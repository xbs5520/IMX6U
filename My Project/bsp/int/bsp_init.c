#include "bsp_int.h"

static unsigned int irqNesting;

//table of interrupt handlers
static sys_irq_handler_t irqTable[NUMBER_OF_INT_VECTORS];

void int_Init(void)
{
    GIC_Init();
    system_irq_handler_init();
    __set_VBAR((uint32_t)0x87800000);
}

void system_irqtable_init(void)
{
    unsigned int i = 0;
    irqNesting = 0;
    // Initialize all interrupt handlers to default handler
    for (int i = 0; i < NUMBER_OF_INT_VECTORS; i++) {
        system_register_irqhandler((IRQn_Type)i, default_irq_handler, NULL);
    }
}

void system_register_irqhandler(IRQn_Type irq, system_irq_handler_t handler, void *userParam)
{
    irqTable[irq].handler = handler;
    irqTable[irq].param = userParam;
}

void system_irq_handler(unsigned int giccIar)
{
    uint32_t intNum = giccIar & 0x3FFUL;

    // check if the interrupt number is valid
    if((1020 == intNum) || (intNum >= NUMBER_OF_INT_VECTORS)) {
        return; // Invalid interrupt number
    }

    irqNesting++;   // Increment nesting level

    // accroding giccIar to get interrupt function pointer
    irqTable[intNum].handler(intNum, irqTable[intNum].param);

    irqNesting--;   // Decrement nesting level
}

void default_irq_handler(unsigned int giccIar, void *userParam)
{
    while(1)
    {
    }
}