#include <unistd.h> 
#include "../imx6ul/imx6ul.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/clk/bsp_clk.h"
#include "../bsp/beep/bsp_beep.h"
#include "../bsp/key/bsp_key.h"
#include "../bsp/int/bsp_int.h"
#include "../bsp/exit/bsp_exit.h"
#include "../bsp/epittimer/bsp_epittimer.h"
#include "../bsp/key_filter/bsp_keyfilter.h"
#include "../bsp/uart/bsp_uart.h"
#include "../stdio/include/stdio.h"
#include "../bsp/lcd/bsp_lcd.h"
#include "../bsp/lcd/bsp_lcdapi.h"
#include "../bsp/rtc/bsp_rtc.h"
#include "../bsp/ap3216c/bsp_ap3216c.h"


int main()
{
    unsigned short ir, als, ps;
    unsigned char state = OFF;

    int_Init();
    imx6u_clkinit();
    delay_Init();
    clk_Enable();
    led_Init();
    beep_Init();
    uart_Init();
    lcd_init();

    tftlcd_dev.forecolor = LCD_YELLOW;
    tftlcd_dev.backcolor = LCD_BLACK;
    lcd_show_string(50, 40, 300, 24, 24,(char*)"Bryan Test");

    while(ap3216c_init())
    {
        lcd_show_string(50, 150, 300, 24, 24,(char*)"AP3216C Check Failed!\n");
        delayms(500);
        lcd_show_string(50, 150, 300, 24, 24,(char*)"PLS check\n");
        delayms(500);
    }

    lcd_show_string(30, 130, 200, 24, 24, (char*)"AP3216C Ready!");
    lcd_show_string(30, 160, 200, 24, 24, (char*)" IR:");
    lcd_show_string(30, 180, 200, 24, 24, (char*)" PS:");
    lcd_show_string(30, 200, 200, 24, 24, (char*)"ALS:");
    tftlcd_dev.forecolor = LCD_BLUE;
    while(1)
    {
        ap3216c_readdata(&ir, &ps, &als); /* 读取数据 */
        lcd_shownum(30 + 32, 160, ir, 5, 24); /* 显示 IR 数据 */
        lcd_shownum(30 + 32, 180, ps, 5, 24); /* 显示 PS 数据 */
        lcd_shownum(30 + 32, 200, als, 5, 24); /* 显示 ALS 数据 */
        delayms(120);
        state = !state;
        led_Switch(LED0, state);
    }
    return 0;
}
