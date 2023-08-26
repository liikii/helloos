section .multiboot_header
; Finally, the dd. It's short for 'define double word'. 
; It declares that we're going to stick some 32-bit data at this location. 
; Remember, when x86 first started, it was a 16-bit architecture set. 
; That meant that the amount of data that could be held in a CPU register 
; (or one 'word' as it's commonly known) was 16 bits. 
; To transition to a 32-bit architecture without losing backwards compatibility, 
; x86 got the concept of a 'double word' or double 16 bits.
; nasm -f elf32 -g -F dwarf multiboot_header.asm
; hexdump -x multiboot_header.o

header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; protected mode code
    dd header_end - header_start ; header length
    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))

    ; Here we use dw to define a 'word' instead of just data. 
    ; Remember a 'word' is 16 bits or 2 bytes on the x86_64 architecture. 
    ; The multiboot specification demands that this be exactly a word. 
    ; You'll find that this is super common in operating systems: 
    ; the exact size and amount of everything matters. 
    ; It's just a side-effect of working at a low level.
     ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:
