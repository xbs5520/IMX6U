#ifndef _BSP_KEY_H
#define _BSP_KEY_H 

#include "../../imx6ul/imx6ul.h"

enum keyvalue {
    KEY_NONE = 0,
    KEY0_VALUE,
};

void key_Init();

int key_getvalue();


#endif /* _BSP_KEY_H */