#ifndef SYSTEM_H
#define SYSTEM_H

#define NULL 0

typedef unsigned long long uint64_t;
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


// Register structs for interrupt/exception
typedef struct registers
{
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
}register_t;


// Register structs for bios service
typedef struct register16 {
    uint16_t di;
    uint16_t si;
    uint16_t bp;
    uint16_t sp;
    uint16_t bx;
    uint16_t dx;
    uint16_t cx;
    uint16_t ax;

    uint16_t ds;
    uint16_t es;
    uint16_t fs;
    uint16_t gs;
    uint16_t ss;
    uint16_t eflags;
}register16_t;



unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);

void *memcpy(void* dst, const void* src, int n);
void *memset(void * dst, char val, int n);
uint16_t * memsetw(uint16_t *dest, uint16_t val, uint32_t count);
uint32_t * memsetdw(uint32_t *dest, uint32_t val, uint32_t count);

int strlen(const unsigned char * s);

#endif
