#include "bsp_keyfilter.h"

static unsigned char state = OFF;

void filterkey_Init()
{

    _gpio_pin_config_t keyconfig;

    // init IO
    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18, 0xF080);

    // set GPIO as Interrupt mode
    keyconfig.direction = kGPIO_DigitalInput;
    keyconfig._gpio_interrupt_mode = kGPIO_IntFallingEdge;
    keyconfig.outputLogic = 1;
    gpio_init(GPIO1, 18, &keyconfig); // Initialize GPIO1_IO18 with the configuration

    // enable GIC Interrupt 
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    // register handler 
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)gpio1_16_31_irqhandler, NULL); // Register the GPIO1 IO18 interrupt handler)

    gpio_enableinit(GPIO1, 18); // Enable GPIO1 IO18 interrupt
    filtertimer_Init(660000); // 10ms
}



void filtertimer_Init(unsigned int val)
{
    EPIT1->CR = 0; // clear
    EPIT1->CR = (1 << 24) | (1 << 3) | (1 << 2) | (1 << 1); // 设置 CR 同 epittimer中 分频为0 66MHZ
    EPIT1->LR = val;
    EPIT1->CMPR = 0; // 比较寄存器为0

    GIC_EnableIRQ(EPIT1_IRQn); // 使能中断
    system_register_irqhandler(EPIT1_IRQn, filtertimer_Irqhandler, NULL);
}

void filtertimer_Stop()
{
    EPIT1->CR &= ~(1 << 0); // 关闭 EPIT1
}
void filtertimer_Restart(unsigned int val)
{
    EPIT1->CR &= ~(1 << 0); // 关闭 EPIT1
    EPIT1->LR = val;
    EPIT1->CR |= (1 << 0); // 打开 EPIT1
}

void filtertimer_Irqhandler()
{
    if(EPIT1->SR & (1 << 0))
    {
        filtertimer_Stop();
        if(gpio_pinread(GPIO1, 18) == 0) // Check if the key is still pressed
        {
            state = !state; // Toggle state
            beep_Switch(state); // Toggle beep state
        }
    }
    EPIT1->SR |= (1 << 0); // 清除中断标记
}
void gpio1_16_31_irqhandler()
{
    filtertimer_Restart(660000);
    gpio_clearintflags(GPIO1, 18); // Clear the interrupt flag for GPIO1 IO18
}