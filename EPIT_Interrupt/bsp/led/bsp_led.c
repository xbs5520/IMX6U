#include "bsp_led.h"

void led_Init()
{
    //set gpio 3
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);
    // set PAD GPIO config
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);
    // set IO03 to Out mode
    GPIO1->GDIR |= (1 << 3);
    // set default led low(open)
    GPIO1->DR &= ~(1 << 3);
}

void led_Switch(int led, int status)
{
    switch(led)
    {
        case LED0:
            if(ON == status)
                GPIO1->DR &= ~(1 << 3);     //open LED
            else if(OFF == status)
                GPIO1->DR |= (1 << 3);      //close LED
            break;
    }
}