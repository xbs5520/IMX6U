#include"bsp_delay.h"

void delay_Short(volatile unsigned int n)
{
    while(n--) {}
}

void delay(volatile unsigned int n)
{
    while(n--)
    {
        delay_Short(0X7FF);
    }
}