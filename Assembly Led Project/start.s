
.global _start

_start:

/* set CCGR0 - CCGR6 Enbale*/
ldr r0, =0X020C4068 
ldr r1, =0XFFFFFFFF
str r1, [r0]

ldr r0, =0X020C406C
str r1, [r0]

ldr r0, =0X020C4070
str r1, [r0]

ldr r0, =0X020C4074
str r1, [r0]

ldr r0, =0x020C4078
str r1, [r0]

ldr r0, =0X020C407C
str r1, [r0]

ldr r0, =0X020C4080
str r1, [r0]

/* MUX_ set GPIO 3 */
ldr r0, =0X020E0068
ldr r1, =0X5
str r1, [r0]

/* set IO config PAD GPIO*/
/*
bit 16      ->  0   disable HYS
bit 15 14   ->  00  Pulldown by default
bit 13      ->  0   keeper on
bit 12      ->  1   enable keeper/pull
bit 11      ->  0   Disable Open Drain(开路输出)
bit 7 6     ->  10  100Mhz
bit 543     ->  110 R0_6 
bit 0       ->  0   slow Rate
0001 0000 1011 0000 -> 0X10B0
*/
ldr r0, =0X020E02F4
ldr r1, =0X10B0
str r1, [r0]

/*
set IO03 as out
set GPIO1_GDIR bit 3 = 1
03000 -> 0X8
*/
ldr r0, =0X0209C004
ldr r1, =0X8
str r1, [r0]

/*
Open Led0
set GPIO1_IO03 low  -> GPIO1_DR
*/
ldr r0, =0X0209C000
ldr r1, =0
str r1, [r0]

/*loop*/
loop:
    b loop
