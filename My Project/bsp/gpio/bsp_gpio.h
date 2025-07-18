/*
 * GPIO driver header file for IMX6UL
 * Provides GPIO pin configuration and control functions
 *
 * Author: Bryan
 * Date: July 18, 2025
 *
 * This file defines data structures and function prototypes for initializing and controlling GPIO pins.
 */

#ifndef _BSP_GPIO_H
#define _BSP_GPIO_H
#include "../../imx6ul/imx6ul.h"

/* GPIO pin direction enumeration */
typedef enum _gpio_pin_direction {
    kGPIO_DigitalInput = 0U,   /* Pin configured as digital input */
    kGPIO_DigitalOutput = 1U   /* Pin configured as digital output */
} _gpio_pin_direction_t;

/* GPIO pin configuration structure */
typedef struct _gpio_pin_config {
    _gpio_pin_direction_t direction; /* Pin direction (input/output) */
    uint8_t outputLogic;             /* Default output logic level (0 or 1) */
} _gpio_pin_config_t;

/* Initializes a GPIO pin with the specified configuration */
void gpio_init(GPIO_Type *gpioType, int pin, _gpio_pin_config_t *config);

int gpio_pinread(GPIO_Type *gpioType, int pin);

/* Sets the output value of a GPIO pin */
void gpio_pinwrite(GPIO_Type *gpioType, int pin, int val);


#endif /* _BSP_GPIO_H */