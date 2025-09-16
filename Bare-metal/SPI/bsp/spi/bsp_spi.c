#include "bsp_spi.h"

// init spi
void spi_init(ECSPI_Type *base)
{
    base->CONREG = 0;
    base->CONREG |= (1 << 0) | (1 << 3) | (1 << 4) | (7 << 20);

    base->CONFIGREG = 0;

    base->PERIODREG = 0x2000;

    // set SPI CLK=6MHz
    base->CONREG &= ~((0XF << 12) | (0XF << 8)); // clear bit15:12 bit11:8
    base->CONREG |= (9 << 12);  // devide 10 60M/10=6MHz
}


unsigned char spich0_readwrite_byte(ECSPI_Type *base, unsigned char txdata)
{
    uint32_t spirxdata = 0;
    uint32_t spitxdata = txdata;

    // channel 0
    base->CONREG &= ~(3 << 18); /*清零 */
    base->CONREG |= (0 << 18);

    // write
    while((base->STATREG & (1 << 0)) == 0);
    base->TXDATA = spitxdata;

    // read
    while((base->STATREG & (1 << 3)) == 0);
    spirxdata =  base->RXDATA;

    return spirxdata;
}