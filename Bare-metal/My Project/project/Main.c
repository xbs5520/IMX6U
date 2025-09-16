#include <unistd.h> 
#include "../imx6ul/imx6ul.h"
#include "../bsp/led/bsp_led.h"
#include "../bsp/delay/bsp_delay.h"
#include "../bsp/clk/bsp_clk.h"
#include "../bsp/beep/bsp_beep.h"
#include "../bsp/key/bsp_key.h"
int main()
{
    int key_Val = 0;
    unsigned char led_Status = OFF;
    unsigned char beep_Status = OFF;

    clk_Enable();   
    led_Init();
    beep_Init();
    key_Init();

    while(1)
    {
        key_Val = key_getvalue();
        if(key_Val)
        {
            switch(key_Val)
            {
                case KEY0_VALUE:
                    beep_Status = !beep_Status; // Toggle反转 beep status
                    beep_Switch(beep_Status);
                    led_Status = !led_Status; // Toggle LED status
                    led_Switch(LED0, led_Status);
                    break;
            }
        }
    }
    return 0;
}
