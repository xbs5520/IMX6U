cross-complie = arm-linux-gnueabihf-
objs := start.o Main.o
all: clean ledc.bin
ledc.bin:$(objs)
	$(cross-complie)ld -Tlink.lds -o ledc.elf $^
	$(cross-complie)objcopy -O binary -S ledc.elf $@
	$(cross-complie)objdump -D -m arm ledc.elf > ledc.dis
%.o:%.s
	$(cross-complie)gcc -Wall -nostdlib -c -o $@ $<
%.o:%.S
	$(cross-complie)gcc -Wall -nostdlib -c -o $@ $<
%.o:%.c
	$(cross-complie)gcc -Wall -nostdlib -c -o $@ $<
clean:
	rm -rf *.o ledc.bin ledc.elf ledc.dis