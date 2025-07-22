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

void clk_Init()
{
    unsigned int reg = 0;

    // 1 set ARM core clock to 528Mhz
    // 1.1 if main chage it to 24Mhz step clock
    if((0 == ((CCM->CCSR >> 2) & 0x1))) // pull_main_clk
    {
        CCM->CCSR &= ~(1 << 8); // step_clk 24Mhz
        CCM->CCSR |= (1 << 2); // set step_clk
    }

    // 1.2 set main 1056    ---  528*2
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0X7F);
    CCM->CCSR &= ~(1 << 2); // set CMM to main
    CCM->CACRR = 1; // set ARM clock divider to 2  ---  1056 / 2 = 528

    // 2 set PLL2(SYS PLL)
    reg = CCM_ANALOG->PLL_SYS;
    reg &= ~(0X3F3F3F3F);       // clear all bits
    reg |= 32 << 24;            // PLL_FD3 528*18/32 = 297Mhz
    reg |= 24 << 16;            // PLL_FD2 528*18/24 = 396Mhz
    reg |= 16 << 8;             // PLL_FD1 528*18/16 = 594Mhz
    reg |= 27 << 0;             // PLL_FD0 528*18/27 = 352Mhz
    CCM_ANALOG->PLL_SYS = reg;  // write back to PLL_SYS

    // 3 set PLL3(USB1) 
    reg = 0;                    //clear reg
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0X3F3F3F3F);       // clear all bits
    reg |= 19 << 24;            // PFD3 480*18/19 = 454.7Mhz
    reg |= 17 << 16;            // PFD2 480*18/17 = 508.25Mhz
    reg |= 16 << 8;             // PFD1 480*18/16 = 540Mhz
    reg |= 12 << 0;             // PFD0 480*18/12 = 720Mhz
    CCM_ANALOG->PFD_480 = reg;  // write back to PFD

    // 4 set AHB min 6 MHZ max 132 Mhz
    CCM->CBCMR &= ~(3 << 18); // clear AHB_PODF
    CCM->CBCMR |= (1 << 18); // pre_periph_clk = PLL2_PDF2 = 396Mhz
    CCM->CBCDR &= ~(1 << 25); //periph_clk = pre_periph_clk = 396
    while((CCM->CDHIPR & (1 << 5))); // wait for AHB clock ready

    // 5 set IPG_CLK_ROOT min 3MHZ max 66Mhz
    CCM->CBCDR &= ~(3 << 24); // clear IPG_PODF
    CCM->CBCDR |= (1 << 8); // set devide 2 IPG_CLK_Root = 66

    // 6 set PERCLK_CLK_ROOT 
    CCM->CSCMR1 &= ~(1 << 7); // set PERCLK_CLK_ROOT as IPG 
    CCM->CSCMR1 &= (7 << 0); // set PERCLK_PODF = 0 devide 1
}

/* 初始化时钟 */
void imx6u_clkinit(void)
{
    unsigned int reg = 0;
    /* 初始化6U的主频为528MHz */
    if(((CCM->CCSR >> 2) & 0X1) == 0) /* 当前时钟使用pll1_main_clk也就是PLL1 */
    {
        CCM->CCSR &= ~(1 << 8); /* 设置step_clk = osc_clk=24M */
        CCM->CCSR |= (1 << 2);  /* pll1_sw_clk=step_clk=24MHz */
    }

    /* 设置PLL1=1056MHz */
    CCM_ANALOG->PLL_ARM = (1 << 13) | ((88 << 0) & 0x7f);
    CCM->CACRR = 1; /* 设置2分频 */
    CCM->CCSR &= ~(1 << 2); /* 设置pll1_sw_clk=pll1_main_clk=1056MHz */

    /* 设置PLL2的4路PFD */
    reg = CCM_ANALOG->PFD_528;
    reg &= ~(0x3F3F3F3F);
    reg |= (32 << 24);                    /* PLL2_PFD3=297MHz*/
    reg |= (24 << 16);                     /* PLL2_PFD2=396MHz*/
    reg |= (16 << 8);                     /* PLL2_PFD1=594MHz*/
    reg |= (27 << 0);                      /* PLL2_PFD0=352MHz*/
    CCM_ANALOG->PFD_528 = reg;

    /* 设置PLL3的4路PFD */
    reg = 0;
    reg = CCM_ANALOG->PFD_480;
    reg &= ~(0x3F3F3F3F);
    reg |= (19 << 24);                    /* PLL3_PFD3=454.7MHz*/
    reg |= (17 << 16);                     /* PLL3_PFD2=508.2MHz*/
    reg |= (16 << 8);                     /* PLL3_PFD1=540MHz*/
    reg |= (12 << 0);                      /* PLL3_PFD0=720MHz*/
    CCM_ANALOG->PFD_480 = reg;


    /* 设置AHB_CLK_ROOT=132MHz */
    CCM->CBCMR &= ~(3 << 18);
    CCM->CBCMR |= 1 << 18;  /* 设置pre_periph clock=PLL2_PFD2=396MHZ */
    CCM->CBCDR &= ~(1 << 25); 
    while(CCM->CDHIPR & (1 << 5)); /* 等待握手信号 */

#if 0
    CCM->CBCDR &= ~(7 << 10);
    CCM->CBCDR |= (2 << 10);    /* 3分频率 */
    while(CCM->CDHIPR & (1 << 1)); /* 等待握手信号 */
#endif

    /* IPG_CLK_ROOT=66MHz */
    CCM->CBCDR &= ~(3 << 8);
    CCM->CBCDR |= (1 << 8); /* IPG_CLK_ROOT=AHB_CLK_ROOT/2=132/2=66MHz */

    /* PERCLK_CLK_ROOT=66MHz */
    CCM->CSCMR1 &= ~(1 << 6);   /* PERCLK_CLK_ROOT时钟源为IPG_CLK=66mhZ */
    CCM->CSCMR1 &= ~(0x3f << 0); /* 1分频，PERCLK_CLK_ROOT=66mHZ */

}
