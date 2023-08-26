; nasm -f elf32 -g -F dwarf boot.asm
; That's what GRUB does: "Call the function named start.
;  start: is a label. GRUB uses this conventional label to know where to begin.
; global start, says "I'm going to define a label start, 
; and I want it to be available outside of this file.
; If we don't say this, GRUB won't know where to 
; find its definition. You can kind of think of it 
; like a 'public' annotation in other languages.
global start 
section .text

; we have bits 32. GRUB will boot us into protected mode, aka
; 32-bit mode (similar to how xv6 bootloader starts in 16-bit real
; mode GRUB will be loaded by the BIOS and will switch into
; protected 32-bit mode for us). But we have to specify directly that
; assembler has to generate 32bit code. Our Hello World will only be in
; 32 bits.

bits 32
start:
    mov word [0xb8000], 0x0248 ; H
    mov word [0xb8002], 0x0265 ; e
    mov word [0xb8004], 0x026c ; l
    mov word [0xb8006], 0x026c ; l
    mov word [0xb8008], 0x026f ; o
    mov word [0xb800a], 0x022c ; ,
    mov word [0xb800c], 0x0220 ;
    mov word [0xb800e], 0x0277 ; w
    mov word [0xb8010], 0x026f ; o
    mov word [0xb8012], 0x0272 ; r
    mov word [0xb8014], 0x026c ; l
    mov word [0xb8016], 0x0264 ; d
    mov word [0xb8018], 0x0221 ; !
    hlt
