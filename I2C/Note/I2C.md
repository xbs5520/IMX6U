# I2C

I²C is a **serial communication protocol** created by Philips in the 1980s for letting multiple chips on the same board talk to each other with just **two wires**:

- **SDA** (Serial Data)
- **SCL** (Serial Clock)

Compare that to **SPI**, which usually needs at least **four** wires

**Master–Slave system**: one master generates the clock and initiates transfers, slaves respond. (Some devices can be multi-master, but that’s rarer in practice.)

**Addressed communication**: each slave has a 7-bit or 10-bit address. You don’t just shout into the bus—you politely call out the chip’s number first.

**Open-drain lines**: nobody drives the lines high directly. Instead, devices only pull them low, and pull-up resistors restore them high. This prevents short circuits if two devices argue.

**Speeds**:

- Standard: 100 kHz
- Fast: 400 kHz
- Fast Plus: 1 MHz
- High-Speed: 3.4 MHz

## How it works

A typical transaction looks like this:

1. **START** condition: master pulls SDA low while SCL is high.
2. **Address**: master sends 7-bit address + 1 bit for Read/Write.
3. **ACK/NACK**: slave responds with “yep, I’m here” (ACK) or silence (NACK).
4. **Data transfer**: bytes go across SDA, each followed by ACK.
5. **STOP** condition: master releases SDA high while SCL is high.

## Why I2C matters?

It’s the lingua franca for **sensors** (temperature, accelerometers, gyros, light sensors).

It’s the backbone for configuration of chips that don’t need bulk data transfer.

Most **EEPROMs and DACs** are I²C. 

- EEPROMs -- Electrically Erasable Programmable Read-Only Memory

  - You can **store data permanently** even if the power is off.

  - Unlike RAM, which forgets everything when power drops, EEPROM remembers.

  - Example uses: saving device configuration, calibration data, serial numbers.

- DACs -- Digital-to-Analog Converter
  - This is the opposite of an ADC (Analog-to-Digital Converter)
  - Example uses: generating audio waveforms, controlling motor speeds with a voltage signal, or setting reference levels in circuits.

## Why pull-up resistors are required?

I²C uses **open-drain (or open-collector) outputs**.

- That means devices can only pull the line **low** (connect it to ground).
- They cannot push it **high** directly.



Enter the **pull-up resistor**:

- The resistor connects SDA and SCL lines to VCC (say, 3.3V or 5V).
- When nobody is pulling low, the resistor gently pulls the line back to logic high.
- When a device wants to signal a low, it pulls the line down to ground, easily overpowering the weak resistor.



the **value of the pull-up resistor matters**.

- Too large → line rises too slowly (bad signal edges, can’t reach high in time at fast speeds).
- Too small → wastes power, devices struggle to pull it down.
- Typical: 4.7 kΩ for 100 kHz I²C, maybe 2.2 kΩ for 400 kHz, but depends on bus capacitance.



## How clock stretching works (slaves can hold SCL low to slow the master)?

- SCL is also open-drain. The master tries to release it high, but the slave yanks it down to ground.

- As long as the slave holds it low, the bus is “paused.”

- When the slave is ready, it releases SCL, the pull-up resistor brings it high, and communication continues.
- This gives slower devices (like old EEPROMs or sensors doing math internally) a way to tell the master “wait a sec.”
- The master must be designed to check SCL and not just assume it goes high immediately.

clock stretching is the slave’s way of throttling the bus.



## Bus arbitration in multi-master systems.

### How arbitration works

1. Both masters put a **START condition** on the bus.
2. Both start sending bits of the **address + R/W bit**.
3. While sending, each master **also monitors the SDA line**.
   - If a master sends a “1” (releases SDA to float high) but sees the line is actually “0” (because the other master pulled it down), it knows it **lost arbitration**.
   - The winning master is the one sending the dominant “0” bits.
4. The loser immediately stops transmitting and waits for the bus to be free again.

### Why this is possible

- Open-drain = no short circuits if two devices drive at once.
- “0” always dominates over “1.”
- This lets multiple masters start simultaneously, and the bus naturally picks one winner without damage.



## How I²C compares to SPI and UART.

**I²C**: The town hall meeting. Everyone’s in the same room, one person speaks at a time, addresses are called out.

**SPI**: The master barking direct orders to each soldier—fast and efficient but needs lots of lines.

**UART**: Two people on walkie-talkies. Simple, reliable, but only one-to-one.

| Feature             | **I²C** (Inter-Integrated Circuit)    | **SPI** (Serial Peripheral Interface)     | **UART** (Universal Asynchronous Receiver/Transmitter)  |
| ------------------- | ------------------------------------- | ----------------------------------------- | ------------------------------------------------------- |
| **Wires needed**    | 2 (SDA, SCL) + GND                    | 4+ (MOSI, MISO, SCK, CS per slave)        | 2 (TX, RX) + GND                                        |
| **Topology**        | Multi-master, multi-slave (addressed) | Single master, multiple slaves (CS lines) | Point-to-point (1:1)                                    |
| **Speed**           | 100 kHz – 3.4 MHz                     | Tens of MHz (sometimes >100 MHz)          | 300 bps – several Mbps (commonly 115.2 kbps – 12 Mbps)  |
| **Addressing**      | Yes, 7-bit or 10-bit addresses        | No, uses dedicated CS pins                | No built-in addressing                                  |
| **Throughput**      | Moderate                              | High (streaming data)                     | Low to moderate                                         |
| **Pins per device** | Constant (2 for whole bus)            | Grows with number of slaves               | Constant (2 per link)                                   |
| **Clock line**      | Yes (SCL)                             | Yes (SCK)                                 | No (asynchronous, relies on baud rate agreement)        |
| **Hardware needs**  | Pull-up resistors on SDA/SCL          | None special, just push-pull lines        | Usually just a transceiver (RS-232/RS-485 for distance) |
| **Best for**        | Sensors, EEPROMs, small peripherals   | Displays, SD cards, high-speed ADC/DAC    | Debug logs, GPS, modems, simple module comms            |
| **Weak spots**      | Slower, overhead, bus capacitance     | Pin hungry, no addressing                 | Only two devices, no clock, less scalable               |

