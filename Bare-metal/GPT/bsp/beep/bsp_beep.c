#include "bsp_beep.h"


void beep_Init()
{
    //set gpio_5 01
    IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0);
    // set PAD GPIO config   same as led
    IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER1_GPIO5_IO01, 0X10B0);
    // set IO05 01 to Out mode
    GPIO5->GDIR |= (1 << 1);
    // set default beep low(open)
    GPIO5->DR &= ~(1 << 1);
}

void beep_Switch(int status)
{
    if(ON == status)
    {
        GPIO5->DR &= ~(1 << 1);
    }
    else if(OFF == status)
    {
        GPIO5->DR |= (1 << 1);
    }
}