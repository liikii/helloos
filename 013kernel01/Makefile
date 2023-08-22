# $@ = target file
# $< = first dependency
# $^ = all dependencies



TOOLPREFIX = i386-elf-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld


# First rule is the one executed when no parameters are fed to the Makefile
all: os-image.bin


# Notice how dependencies are built as needed
kernel.bin: kernel_entry.o kernel.o
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary


kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@


kernel.o: kernel.c
	$(CC) -ffreestanding -c $< -o $@


# Rule to disassemble the kernel - may be useful to debug
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@


bootsect.bin: bootsect.asm
	nasm $< -f bin -o $@


os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@


run: os-image.bin
	qemu-system-i386 -fda $<


.PHONY: clean
clean:
	-rm *.bin *.o *.dis
