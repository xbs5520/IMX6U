CROSS_COMPILE ?= arm-linux-gnueabihf-
NAME ?= ledc

CC := $(CROSS_COMPILE)gcc
LD := $(CROSS_COMPILE)ld
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump

all: clean ledc.bin

OBJS := start.o Main.o

$(NAME).bin:$(OBJS)
	$(LD) -Tlink.lds -o $(NAME).elf $^
	$(OBJCOPY) -O binary -S $(NAME).elf $@
	$(OBJDUMP) -D -m arm $(NAME).elf > $(NAME).dis

%.o:%.s
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.S
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

%.o:%.c
	$(CC) -Wall -nostdlib -c -O2 -o $@ $<

clean:
	rm -rf *.o $(NAME).bin $(NAME).elf $(NAME).dis