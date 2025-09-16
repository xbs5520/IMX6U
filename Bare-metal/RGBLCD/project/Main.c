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

int main()
{
    int_Init();
    imx6u_clkinit();
    delay_Init();
    clk_Enable();
    led_Init();
    beep_Init();
    uart_Init();
    lcd_init();

    unsigned char state = OFF;
    tftlcd_dev.forecolor = LCD_YELLOW;
    tftlcd_dev.backcolor = LCD_BLACK;
    lcd_show_string(10, 40, 260, 32, 32,(char*)"Bryan Test");
    lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
    lcd_draw_rectangle(10, 52, 766, 290);
    lcd_drawline(10, 52,800, 290);
    lcd_draw_Circle(512, 171, 119);

    while(1)
    {
        state = !state; // Toggle state
        lcd_show_string(10, 40, 260, 32, 32,(char*)"Bryan Test");
        lcd_show_string(10, 80, 240, 24, 24,(char*)"RGBLCD TEST");
        lcd_draw_rectangle(10, 52, 766, 290);
        lcd_drawline(10, 52,800, 290);
        lcd_draw_Circle(512, 171, 119);
        led_Switch(LED0, state); // Toggle LED state
        delayms(1000); // Delay for 500 ms
    }
    return 0;
}
