/*
 * GPIO driver source file for IMX6UL
 * Implements GPIO pin initialization, write, and read functions
 *
 * Author: Bryan
 * Date: July 18, 2025
 */

#include "bsp_gpio.h"

/*
 * Initialize a GPIO pin with the specified configuration.
 * Sets the pin direction and initial output logic.
 */
void gpio_init(GPIO_Type *gpioType, int pin, _gpio_pin_config_t *config)
{
    gpioType->IMR &= ~(0x1U << pin); // Disable interrupt for this pin

    // Set the pin direction
    if (config->direction == kGPIO_DigitalOutput) {
        gpioType->GDIR |= (0x1U << pin); // Set pin as output
        gpio_pinwrite(gpioType, pin, config->outputLogic);
    } else {
        gpioType->GDIR &= ~(1 << pin); // Set pin as input
    }
    // set interrupt mode 
    gpio_initconfig(gpioType, pin, config->_gpio_interrupt_mode);
}

/*
 * Write a value to a GPIO pin.
 * val: 0 = low, 1 = high
 */
void gpio_pinwrite(GPIO_Type *gpioType, int pin, int val)
{
    if (1 == val) {
        gpioType->DR |= (1 << pin); // Set pin high
    } else {
        gpioType->DR &= ~(1 << pin); // Set pin low
    }
}

/*
 * Read the value of a GPIO pin.
 * Stores the pin value (0 or 1) in the provided pointer.
 */
int gpio_pinread(GPIO_Type *gpioType, int pin)
{
    return ((gpioType->DR >> pin) & 0x1); // Read pin value and return it
}

void gpio_initconfig(GPIO_Type *gpioType, unsigned int pin, gpio_interrupt_mode_t pinInterruptMode)
{
    volatile uint32_t *icr;
    uint32_t icrShift;
    icrShift = pin;

    gpioType->EDGE_SEL &= ~(1U << pin);

    // low 16bit
    if(pin < 16)
    {
        icr = &(gpioType->ICR1);
    }
    else    
    {
        icr = &(gpioType->ICR2);
        icrShift -= 16;
    }

    switch(pinInterruptMode)
    {
        case(kGPIO_IntLowLevel):
            *icr &= ~(0x3U << (icrShift * 2));
            break;
        case(kGPIO_IntHighLevel):
            *icr &= (*icr & ~(0x3U << (icrShift * 2))) | (0x1U << (icrShift * 2));
            break;
        case(kGPIO_IntRisingEdge):
            *icr &= (*icr & ~(0x3U << (icrShift * 2))) | (0x2U << (icrShift * 2));
            break;
        case(kGPIO_IntFallingEdge):
            *icr |= 0x3U << (icrShift * 2);
            break;
        case(kGPIO_IntBothEdges):
            gpioType->EDGE_SEL |= (1U << pin); // Enable both edges
            break;
        default:
            break;
    }
}

void gpio_enableinit(GPIO_Type *gpioType, unsigned int pin)
{
    gpioType->IMR |= (1U << pin); // Enable interrupt for this pin
}

void gpio_disableinit(GPIO_Type *gpioType, unsigned int pin)
{
    gpioType->IMR &= ~(1U << pin); // Disable interrupt for this pin
}

void gpio_clearintflags(GPIO_Type *gpioType, unsigned int pin)
{
    gpioType->ISR |= (1U << pin); // Clear interrupt flag for this pin
}

