#ifndef _BSP_DELAY_H
#define _BSP_DELAY_H
#include "../../imx6ul/imx6ul.h"
#include "../int/bsp_int.h"
#include "../led/bsp_led.h"

void delay_Init();
void delayus(unsigned int us);
void delayms(unsigned int ms);
void delay(volatile unsigned int n);
void gpt1_irqhandler();

#endif