
; Some constants for loading higher half kernel
VM_BASE     equ 0xC0000000
PDE_INDEX   equ (VM_BASE >> 22)
PSE_BIT     equ 0x00000010
PG_BIT      equ 0x80000000


section .multiboot
header_start:
    dd 0xe85250d6                ; magic number
    dd 0                         ; protected mode code
    dd header_end - header_start ; header length
    ; checksum
    dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
header_end:


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

; Kernel entry
section .text
extern main
; global low_kernel_entry
; low_kernel_entry equ (kernel_entry - VM_BASE)

global kernel_entry
kernel_entry:
    mov ecx, (TEMP_PAGE_DIRECTORY - VM_BASE)
    ; Enable 4mb pages
    mov ecx, cr4;
    or ecx, PSE_BIT
    mov cr4, ecx

    ; mov eax, cr0;
    mov word [0xb8000], 0x0248 ; H
    mov word [0xb8002], 0x0265 ; e
    mov word [0xb8004], 0x026c ; l

    ; update page directory address, since eax and ebx is in use, have to use ecx or other register
    mov ecx, (TEMP_PAGE_DIRECTORY - VM_BASE)
    mov cr3, ecx

    ; mov eax, TEMP_PAGE_DIRECTORY
    mov word [0xb8006], 0x026c ; l
    mov word [0xb8008], 0x026f ; o
    mov word [0xb800a], 0x022c ; ,

    ; Set PG bit, enable paging
    mov ecx, cr0
    or ecx, PG_BIT
    mov cr0, ecx
    

    mov word [0xb800c], 0x0220 ;
    mov word [0xb800e], 0x0277 ; w
    mov word [0xb8010], 0x026f ; o
    mov word [0xb8012], 0x0272 ; r

    mov esp, stack_top
    ;    ; Upon entry to the os, the bootloader has put a pointer to multiboot information structure in ebx, we can pass it into our kmain(), but we may or may not need to use it
    ;    push ebx
    mov eax, main


    mov word [0xb8014], 0x026c ; l
    mov word [0xb8016], 0x0264 ; d
    mov word [0xb8018], 0x0221 ; !

    
    ; mov esp, stack_top    
    ; ; When control is transfer to the c code, we can throw away the old pageing directory structure and use our own, remember to clear pse bit in cr4 though :)
    ; call main
    jmp eax



    ; update page directory address, since eax and ebx is in use, have to use ecx or other register
    ; mov ecx, (TEMP_PAGE_DIRECTORY - VM_BASE)
    ; mov cr3, ecx

    ; ; Enable 4mb pages
    ; mov ecx, cr4;
    ; or ecx, PSE_BIT
    ; mov cr4, ecx

    ; ; Set PG bit, enable paging
    ; mov ecx, cr0
    ; or ecx, PG_BIT
    ; mov cr0, ecx

    ; ; Why not just jmp higher_half ? If you do that, that will be a relative jmp, so u r jumping to virtual memory around 0x100000, which is fine since we have identity mapped earlier
    ; ; but we also want to change the eip(now point to somewhere around 0x100000) to somewhere around 0xc0100000, so we need to get the absolute address of higher half into ecx, and jmp ecx
    ; lea ecx, [higher_half]
    ; jmp ecx

; higher_half:
;     ; Unmap the first 4mb physical mem, because we don't need it anymore. Flush the tlb too
;     mov dword[TEMP_PAGE_DIRECTORY], 0
;     invlpg[0]


; If kmain return, just keep looping...
loop:
    jmp loop
