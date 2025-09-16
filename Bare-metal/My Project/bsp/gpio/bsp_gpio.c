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
    // Set the pin direction
    if (config->direction == kGPIO_DigitalOutput) {
        gpioType->GDIR |= (1 << pin); // Set pin as output
        gpioType->DR = (gpioType->DR & ~(1 << pin)) | (config->outputLogic << pin); // Set initial output value
    } else {
        gpioType->GDIR &= ~(1 << pin); // Set pin as input
    }
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
    return (gpioType->DR >> pin) & 0x1; // Read pin value and return it
}