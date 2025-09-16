cross-complie = arm-linux-gnueabihf-
start.bin:start.elf
	$(cross-complie)objcopy -O binary -S -g start.elf start.bin
start.elf:*.o
	$(cross-complie)ld -Ttext 0X87800000 *.o -o start.elf
*.o:*.s
	$(cross-complie)gcc -g -c *.s
	
#arm-linux-gnueabihf-objdump -D start.elf > start.dis
clean:
	rm -rf *.o *.bin *.elf 
#*.dis