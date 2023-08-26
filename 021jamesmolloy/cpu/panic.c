#include "panic.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"


void panic(char *message, char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    kprint("PANIC(");
    kprint(message);
    kprint(") at ");
    kprint(file);
    kprint(":");

    char s[32];
    int_to_ascii(line, s);
    kprint(s);

    kprint("\n");
    // Halt by going into an infinite loop.
    for(;;);
}

void panic_assert(char *file, u32int line, char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    kprint("ASSERTION-FAILED(");
    kprint(desc);
    kprint(") at ");
    kprint(file);
    kprint(":");
    
    char s[32];
    int_to_ascii(line, s);
    kprint(s);
    

    kprint("\n");
    // Halt by going into an infinite loop.
    for(;;);
}
