#include "bsp_exit.h"

void exit_Init()
{
    _gpio_pin_config_t key_config;
    // set IO config same with bsp_key.c
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    // set GPIO as Interrupt mode
    key_config.direction = kGPIO_DigitalInput;
    key_config._gpio_interrupt_mode = kGPIO_IntFallingEdge;
    key_config.outputLogic = 1;
    gpio_init(GPIO1, 18, &key_config); // Initialize GPIO1_IO18 with the configuration

    // enable GIC Interrupt 
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    // register handler 
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_io18_irqhandler, NULL); // Register the GPIO1 IO18 interrupt handler)
    // enbale Interrupt
    gpio_enbaleinit(GPIO1, 18); // Enable GPIO1 IO18 interrupt
}   

void gpio1_io18_irqhandler()
{
    static unsigned char state = 0;

    delay(10); // Debounce delay
    if(0 == gpio_pinread(GPIO1, 18)) // Check if the key is pressed
    {
        state = !state; // Toggle state
        beep_Switch(state); // Toggle beep state
    }

    gpio_clearintflags(GPIO1, 18); // Clear the interrupt flag for GPIO1 IO18
}