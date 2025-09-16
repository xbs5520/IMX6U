#ifndef _BSP_INT_H
#define _BSP_INT_H

#include "../../imx6ul/imx6ul.h"

/* format of interrupt function*/
typedef void (*system_irq_handler_t)(unsigned int giccIar, void *param);

typedef struct _sys_irq_handler {
    system_irq_handler_t handler; /* interrupt handler function */
    void *param;                  /* parameter for the handler */
} sys_irq_handler_t;

void int_Init(void);
void system_irqtable_init(void);
void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *userParam);
void system_irq_handler(unsigned int giccIar);
void default_irq_handler(unsigned int giccIar, void *userParam);

#endif /* _BSP_INT_H */