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
int main()
{
    int_Init();
    imx6u_clkinit();
    delay_Init();
    clk_Enable();
    led_Init();
    beep_Init();
    uart_Init();
    //unsigned char c = 0;
    unsigned char state = OFF;
    char str[20];
    int a, b;
    while(1)
    {
        // puts("Please input a character: \n");
        // c = getchar(); // Read character from UART
        // puts("\nYou entered: \n");
        // putc(c);
        // puts("\r\n");


        printf("Please input a && b: \n");
        scanf("%d %d", &a, &b);
        printf("\nSum = %d\n", a + b);
        printf("Please input str: \n");
        scanf("%s", str);
        printf("\nYou entered: %s\n", str);
        state = !state; // Toggle state
        led_Switch(LED0, state); // Toggle LED state
    }
    return 0;
}
