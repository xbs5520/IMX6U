#include "bsp_epittimer.h"

// frac Prescaler 分频器
// Tout = ((frac + 1) * val) / Tclk(66Mhz)
// val  倒计数值
void epit1_Init(unsigned int frac, unsigned int val)
{
    if(frac > 0xFFF)
    {
        frac = 0xFFF; // 最大值 12位
    }
    EPIT1->CR = 0; // clear

    // 设置 CR
    // 25:24    01 选择 IPG_CLK 66 Mhz
    // 15:4     frac倍分频
    // 3      从LR重新加载 1
    // 2      使能 1 
    // 1      初始计数器来源与 LR
    // 0      先关闭 后续打开
    EPIT1->CR = (1 << 24) | (frac << 4) | (1 << 3) | (1 << 2) | (1 << 1);
    EPIT1->LR = val; // 设置倒计数值
    EPIT1->CMPR = 0; // 比较寄存器值

    GIC_EnableIRQ(EPIT1_IRQn); // 使能中断

    system_register_irqhandler(EPIT1_IRQn, epit1_Irqhandler, NULL); // 注册中断处理函数

    EPIT1->CR |= 1 << 0; // 打开 EPIT1
}


void epit1_Irqhandler()
{
    static unsigned char state = 0;
    state = !state;
    if(EPIT1->SR & (1 << 0)) // 事件是否发生
    {
        led_Switch(LED0, state);
    }
    EPIT1->SR |= 1 << 0; // 清除中断标记
}