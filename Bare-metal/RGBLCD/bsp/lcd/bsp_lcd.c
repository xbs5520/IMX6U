#include "bsp_lcd.h"

// 液晶屏幕参数
struct tftlcd_typedef tftlcd_dev;

void lcd_init(void)
{
    lcdgpio_init();
    lcd_reset();            //复位
    delayms(10);            //等待复位完成
    lcd_noreset();          //结束复位

    unsigned short lcdid = 0;
    lcdid = lcd_read_panelid();
    printf("LCD ID=%#X\r\n", lcdid);
    tftlcd_dev.height = 480;	
    tftlcd_dev.width = 800;
    tftlcd_dev.vspw = 3;
    tftlcd_dev.vbpd = 32;
    tftlcd_dev.vfpd = 13;
    tftlcd_dev.hspw = 48;
    tftlcd_dev.hbpd = 88;
    tftlcd_dev.hfpd = 40;
    lcdclk_init(42, 4, 8);   //初始化时钟 两次分频为   24 * 3 / 2 / 4 = 9 

    tftlcd_dev.pixsize = 4;
    tftlcd_dev.framebuffer = LCD_FRAMEBUF_ADDR;
    tftlcd_dev.backcolor = LCD_BLACK;
    tftlcd_dev.forecolor = LCD_YELLOW;


    // CTRL
    // 31       0   写1复位
    // 19       1   旁路计数 
    // 17       1   工作在dotclk模式
    // 1514     00  输入数据不交换
    // 1312     00  csc不交换
    // 1110     11  24位
    // 9 8      11  24位 RGB88
    // 5        1   eLCDIF 工作在主模式
    // 1        0   24位都有效
    LCDIF->CTRL = 0;
    LCDIF->CTRL |= (0 << 31) | (1 << 19) | (1 << 17) | (0x00 << 14) | (0x00 << 12) | (0x03 << 10) | (0x03 << 8) | (1 << 5) | (0 << 1);

    //LCDIF->CTRL1 
    // 19:16   0x7  ARGB 24位 
    LCDIF->CTRL1 = 0;
    LCDIF->CTRL1 |= 0x7 << 16;
    // LCDIF_TRANSFER_COUNT
    LCDIF->TRANSFER_COUNT = 0;
    LCDIF->TRANSFER_COUNT = (tftlcd_dev.height << 16) | (tftlcd_dev.width << 0);

    //LCDIF_VDCTRL0
    // 29       0   VSYNC 是输出
    // 28       1   enable 数据线
    // 27       0   VSYNC 是低电平有效
    // 26       0   HSYNC 是低电平有效
    // 25       0   DOTCLK 上升沿有效
    // 24       1   Enbale 信号 高电平有效
    // 2120    11   DOTCLK 模式下都设置位1
    // 17：0    vspw参数
    LCDIF->VDCTRL0 = 0;
    LCDIF->VDCTRL0 |= (0 << 29) | (1 << 28) | (0 << 27) | (0 << 26) | (0 << 25) | (1 << 24) | (0x03 << 20) | (tftlcd_dev.vspw << 0);

    // LCDIF_VDCTRL1
    LCDIF->VDCTRL1 = tftlcd_dev.height + tftlcd_dev.vspw + tftlcd_dev.vfpd + tftlcd_dev.vbpd;

    // LCDIF_VDCTRL2
    LCDIF->VDCTRL2 = (tftlcd_dev.hspw << 18) | (tftlcd_dev.width + tftlcd_dev.hspw + tftlcd_dev.hbpd + tftlcd_dev.hfpd);

    // LCDIF_VDCTRL3
    LCDIF->VDCTRL3 = (tftlcd_dev.hspw + tftlcd_dev.hbpd) << 16 | (tftlcd_dev.vspw + tftlcd_dev.vbpd);


    // LCDIF_VDCTRL4
    // 18      1   同步信号使能
    // 17：0   width
    LCDIF->VDCTRL4 = (1 << 18) | (tftlcd_dev.width);

    //设置当前显存地址和下一帧地址
    LCDIF->CUR_BUF = tftlcd_dev.framebuffer;
    LCDIF->NEXT_BUF = tftlcd_dev.framebuffer;


    lcd_enable();
    delayms(20);
    lcd_clear(LCD_BLACK); //清屏 
}
void lcdgpio_init(void)
{
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23,0);

	IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK,0);	
	IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0);	
	IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0);


	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23,0xB9);

	IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0xB9);

    //点亮
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08 ,0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08 ,0X10b0);

    //背光GPIO初始化
    _gpio_pin_config_t gpio_config;
    gpio_config.direction = kGPIO_DigitalOutput;
    gpio_config.outputLogic = 1;
    gpio_init(GPIO1, 8, &gpio_config);
}

void lcdclk_init(unsigned char loopDiv, unsigned char prediv, unsigned char div)
{
    CCM_ANALOG->PLL_VIDEO_NUM = 0;  //不使用小数分频器
    CCM_ANALOG->PLL_VIDEO_DENOM = 0;

    // 20:19    2   设置 potDivvider一分频
    // 13       1   使能videoPLL
    // 6:0     设置loopDivider分频
    CCM_ANALOG->PLL_VIDEO = (2 << 19) | (1 << 13) | (loopDiv << 0);

    // // MIS2 寄存器
    // CCM_ANALOG->MISC2 &= ~(3 << 30);
    // CCM_ANALOG->MISC2 = 0 << 30;

    // 设置 LCDIF_PRE_CLK 使用PLL5
    CCM->CSCDR2 &= ~(7 << 15);
    CCM->CSCDR2 |= (2 << 15);

    // 设置LCDIF_PRE分频
    CCM->CSCDR2 &= ~(7 << 12);
    CCM->CSCDR2 |= (prediv - 1) << 12;

    // 设置LCDIF分频
    CCM->CBCMR &= ~(7 << 23);
    CCM->CBCMR |= (div - 1) << 23;

    // 设置LCD时钟源位 LCDIF_PRE
    CCM->CSCDR2 &= ~(7 << 9);
    CCM->CSCDR2 |= (0 << 9);
}
void lcd_reset()
{
    LCDIF->CTRL |= (1 << 31); // 强制复位
}
void lcd_noreset()
{
    LCDIF->CTRL &= ~(1 << 31);
}
void lcd_enable()
{
    LCDIF->CTRL |= 1 << 0; // 使能ELCDIF
}

inline void lcd_drawpoint(unsigned short x, unsigned short y, unsigned int color)
{
    *(unsigned int*)((unsigned int)tftlcd_dev.framebuffer +tftlcd_dev.pixsize * (tftlcd_dev.width * y + x)) = color;
}
inline unsigned int lcd_readpoint(unsigned short x, unsigned short y)
{
    return *(unsigned int*)((unsigned int)tftlcd_dev.framebuffer + tftlcd_dev.pixsize * (tftlcd_dev.width * y + x));
}

void lcd_clear(unsigned int color)
{
    unsigned int num;
    unsigned int i = 0;

    unsigned int *startaddr = (unsigned int*) tftlcd_dev.framebuffer;
    num = (unsigned int)tftlcd_dev.width * tftlcd_dev.height;

    for(i = 0; i < num; i++)
    {
        startaddr[i] = color;
    }
}

void lcd_fill(unsigned short x0, unsigned short y0, unsigned short x1, unsigned short y1, unsigned int color)
{
    unsigned int x, y;
    if(x0 < 0) x0 = 0;
    if(y0 < 0) y0 = 0;
    if(x1 >= tftlcd_dev.width) x1 = tftlcd_dev.width - 1;
    if(y1 >= tftlcd_dev.height) y1 = tftlcd_dev.height - 1;

    for(y = y0; y <= y1; y++)
    {
        for(x = x0; x <= x1; x++)
        {
            lcd_drawpoint(x, y, color);
        }
    }
}
unsigned short lcd_read_panelid(void)
{
    unsigned char idx = 0;

    /* 打开模拟开关,设置LCD_VSYNC为高电平 */
    _gpio_pin_config_t lcdio_config;
    IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_GPIO3_IO03, 0); /*复用为GPIO3_IO03 */
    IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_GPIO3_IO03, 0X10b0);

    /* GPIO初始化 */
    lcdio_config.direction = kGPIO_DigitalOutput;
    lcdio_config.outputLogic = 1;
    gpio_init(GPIO3, 3, &lcdio_config);

    /* 读取屏幕ID */
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_GPIO3_IO12, 0);  /* B7(M2) */
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_GPIO3_IO20, 0);  /* G7(M1) */
    IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_GPIO3_IO28, 0);  /* R7(M0) */

    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_GPIO3_IO12, 0XF080);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_GPIO3_IO20, 0XF080);
    IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_GPIO3_IO28, 0XF080);

    lcdio_config.direction = kGPIO_DigitalInput;
    gpio_init(GPIO3, 12, &lcdio_config);
    gpio_init(GPIO3, 20, &lcdio_config);
    gpio_init(GPIO3, 28, &lcdio_config);

    idx = (unsigned char)gpio_pinread(GPIO3, 28); /*  M0 */
    idx |= (unsigned char)gpio_pinread(GPIO3, 20) << 1; /*  M1 */
    idx |= (unsigned char)gpio_pinread(GPIO3, 12) << 2; /*  M2 */

    if(idx == 0) return ATK4342;
    else if(idx == 1) return ATK7084;
    else if(idx == 2) return ATK7016;
    else if(idx == 4) return ATK4384;
    else if(idx == 5) return ATK1018;
    else return 0;
}


