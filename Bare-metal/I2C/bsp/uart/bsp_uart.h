#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "../../imx6ul/imx6ul.h"
#include "../gpio/bsp_gpio.h"

void uart_Init();
void uart_io_Init();
void uart_disable(UART_Type *uart);
void uart_enable(UART_Type *uart);
void uart_softreset(UART_Type *uart);
//void uart_setbaudrate(UART_Type *uart, unsigned int baudrate, unsigned int srcclock_hz);
void putc(unsigned char c);
void puts(char *str);
unsigned char getc();
void raise(int sig_nr);

#endif  // _BSP_UART_H_