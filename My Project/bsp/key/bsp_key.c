#include "bsp_key.h"
#include "../gpio/bsp_gpio.h"
#include "../delay/bsp_delay.h"

void key_Init()
{
    _gpio_pin_config_t key_config;
    
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);

    /* URT1_CTS_B is used as a key input pin.
     bit 16         0           Close HYS
     bit 15 14      11          22k pull-up default
     bit 13         1           Open pull down
     bit 12         1           Enbale pull/keeper
     bit 11         0           Open Drain enbale field
     bit 7 6        10          100Mhz
     bit 5 4 3      000         close output
     bit 0          0           Low Slew Rate   
    */
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0XF080);

    key_config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO1, 18, &key_config);
}

int key_getvalue()
{
    int value = 0;

    static unsigned char release = 1; // Key release state

    if((1 == release) && (0 == gpio_pinread(GPIO1, 18))) // pressd key
    {
        delay(10); // debounce delay
        release = 0; // Key pressed state
        if(0 == gpio_pinread(GPIO1, 18)) // still pressed
        {
            value = KEY0_VALUE; // Return key value
        }
    } 
    else if(1 == gpio_pinread(GPIO1, 18)) // Key released
    {
        value = 0;
        release = 1; // Set to key release state
    }
    return value; // Return key value
}