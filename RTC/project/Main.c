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

int main()
{
    unsigned char key = 0;
    int t = 0;
    int count = 3;
    char buf[256];
    struct rtc_datetime rtc;
    unsigned char state = OFF;

    int_Init();
    imx6u_clkinit();
    delay_Init();
    clk_Enable();
    led_Init();
    beep_Init();
    uart_Init();
    lcd_init();
    rtc_init();

    tftlcd_dev.forecolor = LCD_YELLOW;
    tftlcd_dev.backcolor = LCD_BLACK;
    lcd_show_string(50, 40, 300, 24, 24,(char*)"Bryan Test");

    while(1)
    {
        if(t == 100)
        {
            t = 0;
            printf("will be running %d s ...\r", count);
            lcd_fill(50, 40, 370, 70, tftlcd_dev.backcolor);
            sprintf(buf, "will be running %ds ......", count);
            lcd_show_string(50, 40, 300, 24, 24, buf);
            count--;
            if(count < 0)
                break;
        }

        key = key_getvalue();
        if(key == KEY0_VALUE)
        {
            rtc.year = 2025;
            rtc.month = 10;
            rtc.day = 1;
            rtc.hour = 0;
            rtc.minute = 0;
            rtc.second = 0;
            rtc_setdatetime(&rtc);
            printf("\r\n RTC Init finish\r\n");
            break;
        }
        delayms(10);
        t++;
    }
    tftlcd_dev.forecolor = LCD_YELLOW;
    lcd_fill(50, 40, 370, 70, tftlcd_dev.backcolor);
    lcd_show_string(50, 40, 200, 24, 24, (char*)"Current Time:");
    tftlcd_dev.forecolor = LCD_BLUE;

    while(1)
    {
        rtc_getdatetime(&rtc);
        sprintf(buf, "%4d-%2d-%2d %2d:%2d:%2d", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
        lcd_fill(50, 70, 300, 94, tftlcd_dev.backcolor);
        lcd_show_string(50, 70, 250, 24, 24, (char*)buf);

        state = !state;
        led_Switch(LED0, state);
        delayms(1000);
    }
    return 0;
}
