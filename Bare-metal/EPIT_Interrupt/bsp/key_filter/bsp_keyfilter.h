#ifndef _BSP_KEYFILTER_H
#define _BSP_KEYFILTER_H
#include "../key/bsp_key.h"
#include "../gpio/bsp_gpio.h"
#include "../int/bsp_int.h"
#include "../beep/bsp_beep.h"
#include "../../imx6ul/imx6ul.h"
void filterkey_Init();
void filtertimer_Init(unsigned int val);
void filtertimer_Stop();
void filtertimer_Restart(unsigned int val);
void filtertimer_Irqhandler();
void gpio1_16_31_irqhandler();


#endif  // _BSP_KEYFILTER_H