#include"bsp_delay.h"

void delay_Init()
{
    GPT1->CR = 0; //clear
    GPT1->CR = 1 << 15; // 复位定时器 swr
    while(GPT1->CR >> 15 != 0); //等待复位完成


    // bit 22:20  000 输出比较1的输出功能关闭
    // bit 9      0   Restart模式 
    // bit 8:6    001 时钟源选择IPG 66
    GPT1->CR = (1 << 6);

    // bit 11:0  65 设置 66分频 GPT1时钟为66/66 = 1 Mhz 
    GPT1->PR = (65 << 0);

    // OCR1 将比较值设置为 最大 0XFFFFFFFF
    // 一次就是 0xFFFFFFFFus = 71.5min
    GPT1->OCR[0] = 0xFFFFFFFF;
    GPT1->CR |= (1 << 0); // 使能GPT1

#if 0
    //定时中断设置  和epit一样 目前不适用
    // bit 11:0  65 设置 66分频 GPT1时钟为66/66 = 1 Mhz 
    GPT1->PR = (65 << 0);
    // 这里定时 500ms 产生中断，因此就应该为 1000000/2=500000
    GPT1->OCR[0] = 500000;
    // IR寄存器 使能比较中断
    GPT1->IR |= 1 << 0;
    //使能中断注册中断函数
    GIC_EnableIRQ(GPT1_IRQn);
    system_register_irqhandler(GPT1_IRQn, gpt1_irqhandler, NULL);
#endif
}
void delayus(unsigned int us)
{
    unsigned long oldcnt, newcnt;
    unsigned long totalcnt = 0;
    oldcnt = GPT1->CNT; // 读取当前计数值
    while(1)
    {
        newcnt = GPT1->CNT; // 读取新的计数值
        if (newcnt > oldcnt) //向上计数没有溢出
        {
            totalcnt += (newcnt - oldcnt); // 计算计数差
        }
        else // 溢出了
        {
            totalcnt += (0xFFFFFFFF - oldcnt + newcnt); // 计算溢出后的计数差
        }
        oldcnt = newcnt;
        if(totalcnt >= us) break;
    }
}
void delayms(unsigned int ms)
{
    int i = 0;
    for(; i < ms; i++)
    {
        delayus(1000);
    }
}
void delay_short(volatile unsigned int n)
{
    while(n--){};
}
void delay(volatile unsigned int n)
{
    while(n--);
    {
        delay_short(0x7FF);
    }
}
#if 0
void gpt1_irqhandler()
{
    static unsigned char state = 0;
    state = !state;

    if(GPT1->SR & (1 << 0))
    {
        led_switch(LED0, state); // Toggle LED state
    }
    GPT1->SR |= (1 << 0); //清除中断标志

}
#endif