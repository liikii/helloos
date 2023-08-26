#include "../cpu/isr.h"
// #include "../drivers/screen.h"

// #include "../cpu/timer.h"
// #include "../drivers/keyboard.h"

// void main() {
//     isr_install();

//     asm volatile("sti");
//     init_timer(50);
//     /* Comment out the timer IRQ handler to read
//      * the keyboard IRQs easier */
//     init_keyboard();
// }


// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>

// #include "monitor.h"
// #include "descriptor_tables.h"
// #include "timer.h"
// #include "../cpu/paging.h"


void main() {
    // Initialise all the ISRs and segmentation
    isr_install();

    kprint("Hello, paging world!xyz\n");
    initialise_paging();

    // kprint("Hello, paging world!2\n");
    // Initialise the screen (by clearing it)
    // monitor_clear();

    // initialise_paging();
    // monitor_write("Hello, paging world!\n");

    // u32int *ptr = (u32int*)0xA0000000;
    // u32int do_page_fault = *ptr;

    // return 0;
}
