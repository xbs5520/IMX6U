#ifndef _BSP_EXIT_H
#define _BSP_EXIT_H
#include "../../imx6ul/imx6ul.h"
#include "../gpio/bsp_gpio.h"
#include "../int/bsp_int.h"
#include "../beep/bsp_beep.h"
#include "../delay/bsp_delay.h"

void exit_Init();
void gpio1_io18_irqhandler();


#endif /* _BSP_EXIT_H */