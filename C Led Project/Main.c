#include"Defs.h"
#include <unistd.h> 

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
    CCM_CCGR0 = 0XFFFFFFFF;
    CCM_CCGR1 = 0XFFFFFFFF;
    CCM_CCGR2 = 0XFFFFFFFF;
    CCM_CCGR3 = 0XFFFFFFFF;
    CCM_CCGR4 = 0XFFFFFFFF;
    CCM_CCGR5 = 0XFFFFFFFF;
    CCM_CCGR6 = 0XFFFFFFFF;
    return;
}

void init_Led()
{
    //set gpio 3
    SW_MUX_GPIO1_IO03 = 0X5;

    // set PAD GPIO config
    SW_PAD_GPIO1_IO03 = 0X10B0;

    // set IO03 to Out mode
    GPIO1_GDIR = 0X8;

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
    GPIO1_DR &= ~(1<<3);
}

void led_Off()
{
    //至1 bit3
    GPIO1_DR |= (1<<3);
}
