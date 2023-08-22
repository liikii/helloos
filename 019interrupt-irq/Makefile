# $@ = target file
# $< = first dependency
# $^ = all dependencies
C_SRCS = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)

OBJS = $(C_SRCS:.c=.o cpu/interrupt.o)


TOOLPREFIX = i386-elf-

CC = $(TOOLPREFIX)gcc
LD = $(TOOLPREFIX)ld
GDB = $(TOOLPREFIX)gdb

QEMU = qemu-system-i386


CFLAGS = -g


img: os-image.bin


# First rule is run by default
os-image.bin: boot/bootsect.bin kernel.bin
	cat $^ > os-image.bin


# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: boot/kernel_entry.o ${OBJS}
	$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary


# Used for debugging purposes
kernel.elf: boot/kernel_entry.o ${OBJS}
	$(LD) -o $@ -Ttext 0x1000 $^ 


run: os-image.bin
	$(QEMU) -fda os-image.bin


# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	$(QEMU) -s -fda os-image.bin -d guest_errors,int &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Pattern Rules
# Pattern rules are often used but quite confusing. You can look at them as two ways:

# A way to define your own implicit rules
# A simpler form of static pattern rules

# Generic rules for wildcards
# To make an object, always compile from its .c
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@


.PHONY: clean
clean:
	-rm -rf *.bin *.dis *.o *.elf
	-rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o cpu/*.o
