#include <unistd.h> 
#include "../imx6ul/imx6ul.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/clk/bsp_clk.h"

int main()
{
    clk_Enable();
    led_Init();

    while(1)
    {
        led_Switch(LED0, ON);
        delay(1000);
        led_Switch(LED0, OFF);
        delay(2000);
    }
    return 0;
}
