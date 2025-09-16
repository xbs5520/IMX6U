#ifndef _BSP_LED_H
#define _BSP_LED_H

#include "../imx6ul/imx6ul.h"

#define LED0        0

void led_Init();
void led_Switch(int led, int status);

#endif