SECTIONS
{
    . = 0X87800000;
    .text :
    {
        start.o
        Main.o
        *(.text)
    }
    .rodata ALIGN(4) : {*(.rodata*)}
    .data ALIGN(4) : { *(.data) }
    __bss_start = .;
    .bss ALIGN(4) : { *(.bss) *(COMMON) }
    __bss_end = .;
}