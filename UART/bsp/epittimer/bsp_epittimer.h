#ifndef _BSP_EPITTIMER_H
#define _BSP_EPITTIMER_H
#include "../../imx6ul/imx6ul.h"
#include "../int/bsp_int.h"
#include "../led/bsp_led.h"


void epit1_Init(unsigned int frac, unsigned int val);
void epit1_Irqhandler();

#endif  // _BSP_EPITTIMER_H