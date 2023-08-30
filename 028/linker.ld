/* ld -m elf_i386 -T linker.ld -o kernel.bin multiboot_header.o boot.o */
OUTPUT_FORMAT("elf32-i386")
ENTRY(start)
SECTIONS {
  . = 0x20100000; 
  .rodata ALIGN (4K): AT(ADDR(.rodata)-0x20100000)
  {
    /* ensure that the multiboot header is at the beginning */
    KEEP(*(.multiboot_header))
    *(.rodata .rodata.*)
  }

  .text ALIGN (4K): AT(ADDR(.text)-0x20100000)
  {
    *(.text .text.*)
  }

  .data ALIGN (4K): AT(ADDR(.data)-0x20100000)
  {
    *(.data .data.*)
  }

  .bss ALIGN (4K): AT(ADDR(.bss)-0x20100000)
  {
    *(.bss .bss.*)
    *(.initial_stack)
  }
  /*
        Put a symbol end here, it tells us where all the kernel code/data ends, it means everything after 'end' can be used for something else
    */
    end = .;
}
