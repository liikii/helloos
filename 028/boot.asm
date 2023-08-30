; nasm -f elf32 -g -F dwarf boot.asm
; That's what GRUB does: "Call the function named start.
;  start: is a label. GRUB uses this conventional label to know where to begin.
; global start, says "I'm going to define a label start, 
; and I want it to be available outside of this file.
; If we don't say this, GRUB won't know where to 
; find its definition. You can kind of think of it 
; like a 'public' annotation in other languages.
VM_BASE     equ 0x20000000
PDE_INDEX   equ (VM_BASE >> 22)
PSE_BIT     equ 0x00000010
PG_BIT      equ 0x80000000


section .rodata
;定义各段类型和基
gdt_start: ; don't remove the labels, they're needed to compute sizes and jumps
    ; the GDT starts with a null 8-byte
    dd 0x0 ; 4 byte
    dd 0x0 ; 4 byte

; GDT for code segment. base = 0x00000000, length = 0xfffff
; for flags, refer to os-dev.pdf document, page 36
gdt_code: 
    dw 0xffff    ; segment length, bits 0-15
    dw 0x0       ; segment base, bits 0-15
    db 0x0       ; segment base, bits 16-23
    db 10011010b ; flags (8 bits)
    db 11001111b ; flags (4 bits) + segment length, bits 16-19
    db 0x0       ; segment base, bits 24-31

; GDT for data segment. base and length identical to code segment
; some flags changed, again, refer to os-dev.pdf
gdt_data:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

gdt_end:

; GDT descriptor
gdt_descriptor:
    dw gdt_end - gdt_start - 1 ; size (16 bit), always one less of its true size
    dd gdt_start ; address (32 bit)

; define some constants for later use
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start


section .data
align 4096
global TEMP_PAGE_DIRECTORY
TEMP_PAGE_DIRECTORY:
    ; Map the first 4mb physical memory to first 4mb virtual memory. Otherwise, when paging is enabled, eip points to, 0x100004 for example, and MMU is not gonna know how to translate 
    ; this address into phsyical mem address, because our PDE doesn't tell MMU how to find it.
    dd 0x00000083
    times(PDE_INDEX - 1) dd 0
    dd 0x00000083
    times(1024 - PDE_INDEX - 1) dd 0 

; Our initial stack
section .initial_stack, nobits
align 4
stack_bottom:
    ; 1mb of uninitialized data(1024*1024=104856)
    resb 104856
stack_top:


section .text
global start 

; we have bits 32. GRUB will boot us into protected mode, aka
; 32-bit mode (similar to how xv6 bootloader starts in 16-bit real
; mode GRUB will be loaded by the BIOS and will switch into
; protected 32-bit mode for us). But we have to specify directly that
; assembler has to generate 32bit code. Our Hello World will only be in
; 32 bits.

bits 32
start:
    ; load 0 into all data segment registers
    ; mov ax, DATA_SEG
    ; mov ss, ax
    ; mov ds, ax
    ; mov es, ax
    ; mov fs, ax
    ; mov gs, ax
    ; lgdt [gdt_descriptor]

    ; update page directory address, since eax and ebx is in use, have to use ecx or other register
    mov ecx, (TEMP_PAGE_DIRECTORY - VM_BASE)
    mov cr3, ecx

    ; Enable 4mb pages
    mov ecx, cr4;
    or ecx, PSE_BIT
    mov cr4, ecx

    ; Set PG bit, enable paging
    mov ecx, cr0
    or ecx, PG_BIT
    mov cr0, ecx

    ; Why not just jmp higher_half ? If you do that, that will be a relative jmp, so u r jumping to virtual memory around 0x100000, which is fine since we have identity mapped earlier
    ; but we also want to change the eip(now point to somewhere around 0x100000) to somewhere around 0xc0100000, so we need to get the absolute address of higher half into ecx, and jmp ecx
    lea ecx, [higher_half]
    jmp ecx

higher_half:
    ; Unmap the first 4mb physical mem, because we don't need it anymore. Flush the tlb too
    mov dword[TEMP_PAGE_DIRECTORY], 0
    invlpg[0]

    mov esp, stack_top
    extern main
    ; Upon entry to the os, the bootloader has put a pointer to multiboot information structure in ebx, we can pass it into our kmain(), but we may or may not need to use it
    push ebx
    ; When control is transfer to the c code, we can throw away the old pageing directory structure and use our own, remember to clear pse bit in cr4 though :)
    call main
    ; mov word [0xb8000], 0x0248 ; H
    ; mov word [0xb8002], 0x0265 ; e
    ; mov word [0xb8004], 0x026c ; l
    ; mov word [0xb8006], 0x026c ; l
    ; mov word [0xb8008], 0x026f ; o
    ; mov word [0xb800a], 0x022c ; ,
    ; mov word [0xb800c], 0x0220 ;
    ; mov word [0xb800e], 0x0277 ; w
    ; mov word [0xb8010], 0x026f ; o
    ; mov word [0xb8012], 0x0272 ; r
    ; mov word [0xb8014], 0x026c ; l
    ; mov word [0xb8016], 0x0264 ; d
    ; mov word [0xb8018], 0x0221 ; !
    ; hlt
; If kmain return, just keep looping...
loop:
    jmp loop
