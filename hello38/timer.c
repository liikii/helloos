#include "timer.h"
#include "isr.h"
#include "vga.h"


unsigned int tick = 0;

uint16_t hz = 0;


void set_frequency(uint16_t h) 
{
    hz = h;
    uint16_t divisor = INPUT_CLOCK_FREQUENCY / h;
    // Init, Square Wave Mode, non-BCD, first transfer LSB then MSB
    outb(TIMER_COMMAND, TIMER_ICW);
    outb(TIMER_DATA, divisor & 0xFF);
    outb(TIMER_DATA, (divisor >> 8) & 0xFF);
}



void timer_init() 
{
    // IRQ0 will fire 100 times per second
    // set_frequency(100);
	// IRQ0 will fire 8 times per second
    set_frequency(100);
    register_interrupt_handler(32, timer_handler);
    // wakeup_list = list_create();
}


void timer_handler(register_t * reg) 
{
	tick++;
	put_dec(tick);
	putchar(' ');
}
