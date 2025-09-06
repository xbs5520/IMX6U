CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET ?= bsp

CC 						:= 	$(CROSS_COMPILE)gcc
LD 						:= 	$(CROSS_COMPILE)ld
OBJCOPY 				:= 	$(CROSS_COMPILE)objcopy
OBJDUMP 				:= 	$(CROSS_COMPILE)objdump
LIBPATH 				:= 	-lgcc -L /usr/local/arm/gcc-linaro-4.9.4-2017.01-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/4.9.4

INCDIRS 				:= 	imx6ul \
							stdio/include \
							bsp/clk \
							bsp/led \
							bsp/beep \
							bsp/gpio \
							bsp/key \
							bsp/int \
							bsp/exit \
							bsp/epittimer \
							bsp/key_filter \
							bsp/uart \
							bsp/lcd \
							bsp/delay

SRCDIRS 				:= 	project \
							stdio/lib \
							bsp/clk \
							bsp/led \
							bsp/beep \
							bsp/gpio \
							bsp/key \
							bsp/int \
							bsp/exit \
							bsp/epittimer \
							bsp/key_filter \
							bsp/uart \
							bsp/lcd \
							bsp/delay

INCLUDE 				:= 	$(patsubst %, -I %, $(INCDIRS))
SFILES 					:= 	$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.s))
CFILES					:= 	$(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

SFILENDIR 				:= 	$(notdir $(SFILES))
CFILENDIR 				:= 	$(notdir $(CFILES))

SOBJS 					:= 	$(patsubst %, obj/%, $(SFILENDIR:.s=.o))
COBJS 					:= 	$(patsubst %, obj/%, $(CFILENDIR:.c=.o))
OBJS 					:= 	$(SOBJS) $(COBJS)

VPATH 					:= 	$(SRCDIRS)

.PHONY: clean

$(TARGET).bin : $(OBJS)
	$(LD) -Tlink.lds -o $(TARGET).elf $^ $(LIBPATH)
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -fno-builtin -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -Wa,-mimplicit-it=thumb -nostdlib -fno-builtin  -c -O2 $(INCLUDE) -o $@ $<


clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)