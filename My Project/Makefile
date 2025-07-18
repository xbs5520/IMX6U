CROSS_COMPILE ?= arm-linux-gnueabihf-
TARGET ?= bsp

CC 						:= 	$(CROSS_COMPILE)gcc
LD 						:= 	$(CROSS_COMPILE)ld
OBJCOPY 				:= 	$(CROSS_COMPILE)objcopy
OBJDUMP 				:= 	$(CROSS_COMPILE)objdump

INCDIRS 				:= 	imx6ul \
							bsp/clk \
							bsp/led \
							bsp/beep \
							bsp/gpio \
							bsp/key \
							bsp/delay

SRCDIRS 				:= 	project \
							bsp/clk \
							bsp/led \
							bsp/beep \
							bsp/gpio \
							bsp/key \
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
	$(LD) -Tlink.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf > $(TARGET).dis

$(SOBJS) : obj/%.o : %.s
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

$(COBJS) : obj/%.o : %.c
	$(CC) -Wall -nostdlib -c -O2 $(INCLUDE) -o $@ $<

clean:
	rm -rf $(TARGET).elf $(TARGET).dis $(TARGET).bin $(COBJS) $(SOBJS)