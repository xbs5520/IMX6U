#include "bsp_clk.h"

void clk_Enable()
{
    CCM->CCGR0 = 0XFFFFFFFF;
    CCM->CCGR1 = 0XFFFFFFFF;
    CCM->CCGR2 = 0XFFFFFFFF;
    CCM->CCGR3 = 0XFFFFFFFF;
    CCM->CCGR4 = 0XFFFFFFFF;
    CCM->CCGR5 = 0XFFFFFFFF;
    CCM->CCGR6 = 0XFFFFFFFF;
}

// sysinit clk
void imx6u_clkinit(void)
{
    unsigned int reg = 0;
    // 1 set ARM core clock to 528Mhz
    // 1.1 if main chage it to 24Mhz step clock
    if(((CCM->CCSR >> 2) & 0X1) == 0) // pull_main_clk
    {
        CCM->CCSR &= ~(1 << 8); // step_clk 24Mhz
        CCM->CCSR |= (1 << 2);  // set step_clk
    }

    // 1.2 set main 1056    ---  528*2
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0x7f);
    CCM->CACRR = 1; /* 设置2分频 */
    CCM->CCSR &= ~(1 << 2); /* 设置pll1_sw_clk=pll1_main_clk=1056MHz */

    // 2 set PLL2(SYS PLL)
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3F3F3F3F);       // clear all bits
    reg |= 32 << 24;            // PLL_FD3 528*18/32 = 297Mhz
    reg |= 24 << 16;            // PLL_FD2 528*18/24 = 396Mhz
    reg |= 16 << 8;             // PLL_FD1 528*18/16 = 594Mhz
    reg |= 27 << 0;             // PLL_FD0 528*18/27 = 352Mhz
    CCM_ANALOG->PFD_528 = reg;  // write back to PLL_SYS

    // 3 set PLL3(USB1) 
    reg = 0;                            //clear reg
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0X3F3F3F3F);       // clear all bits
    reg |= 19 << 24;            // PFD3 480*18/19 = 454.7Mhz
    reg |= 17 << 16;            // PFD2 480*18/17 = 508.25Mhz
    reg |= 16 << 8;             // PFD1 480*18/16 = 540Mhz
    reg |= 12 << 0;             // PFD0 480*18/12 = 720Mhz
    CCM_ANALOG->PFD_480 = reg;  // write back to PFD


    // 4 set AHB 132 Mhz
    CCM->CBCMR &= ~(3 << 18); // clear PRE_PERIPH_CLK_SEL
    CCM->CBCMR |= (1 << 18); // pre_periph_clk = PLL2_PDF2 = 396Mhz
    CCM->CBCDR &= ~(1 << 25); //periph_clk = pre_periph_clk = 396
    while((CCM->CDHIPR & (1 << 5))); // wait for AHB clock ready

#if 0 // 默认已经设置好3分配但是由于以下代码有bug 上机会卡死所以暂不设置
    CCM->CBCDR &= ~(7 << 10);
    CCM->CBCDR |= (2 << 10);    /* 3分频率 */
    while(CCM->CDHIPR & (1 << 1)); /* 等待握手信号 */
#endif

    // 5 set IPG_CLK_ROOT 66Mhz
    CCM->CBCDR &= ~(3 << 8); // clear IPG_PODF
    CCM->CBCDR |= (1 << 8);  // set devide 2 IPG_CLK_Root = 66

    // 6 set PERCLK_CLK_ROOT  66Mhz = IPG
    CCM->CSCMR1 &= ~(1 << 6);       // set PERCLK_CLK_ROOT as IPG 
    CCM->CSCMR1 &= ~(0x3f << 0);    // set PERCLK_PODF = 0 devide 1

}
