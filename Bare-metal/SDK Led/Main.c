#include <unistd.h> 
#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "MCIMX6Y2.h"
void colck_Enable();
void init_Led();
void delay(volatile unsigned int n);
void led_On();
void led_Off();
int main()
{
    colck_Enable();
    init_Led();
    while(1)
    {
        led_On();
        delay(500);
        led_Off();
        delay(500);
    }
    

    return 0;
}

// set clock Enable
void colck_Enable()
{
    CCM->CCGR0 = 0XFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
    return;
}

void init_Led()
{
    //set gpio 3
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO03_GPIO1_IO03,0);

    // set PAD GPIO config
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO03_GPIO1_IO03,0X10B0);

    // set IO03 to Out mode
    GPIO1->GDIR |= (1 << 3);

    // set default led low(open)
    GPIO1->DR &= ~(1 << 3);
    return;
}   

void delay_short(volatile unsigned int n)
{
    while(n--)
    {}
    return;
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_short(0X7FF);
    }
    return;
}

void led_On()
{
    //清0 bit3
    GPIO1->DR &= ~(1<<3);
}

void led_Off()
{
    //至1 bit3
    GPIO1->DR |= (1<<3);
}
