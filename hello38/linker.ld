OUTPUT_FORMAT("elf32-i386")
ENTRY(start)

SECTIONS {
  . = 0xC0100000; /* Tells GRUB to load the kernel starting at the 1MB mark */

  .rodata : AT(ADDR(.rodata)-0xC0000000)
  {
    /* ensure that the multiboot header is at the beginning */
    KEEP(*(.multiboot_header))
    *(.rodata .rodata.*)
    . = ALIGN(4K);
  }

  .text ALIGN(4K): AT(ADDR(.text)-0xC0000000)
  {
    *(.text .text.*)
    . = ALIGN(4K);
  }

  .data : AT(ADDR(.data)-0xC0000000)
  {
    *(.data .data.*)
    . = ALIGN(4K);
  }

  .bss : AT(ADDR(.bss)-0xC0000000)
  {
    *(.bss .bss.*)
    . = ALIGN(4K);
  }
}
