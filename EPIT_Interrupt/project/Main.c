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
int main()
{
    int_Init();
    imx6u_clkinit();
    clk_Enable();   
    led_Init();
    beep_Init();
    key_Init();
    filterkey_Init();

    unsigned char state = OFF;
    while(1)
    {
        state = !state; // Toggle state
        led_Switch(LED0, state); // Toggle LED state
        delay(500);
    }
    return 0;
}
