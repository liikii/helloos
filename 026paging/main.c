// main.c -- Defines the C-code kernel entry point, calls initialisation routines.
//           Made for JamesM's tutorials <www.jamesmolloy.co.uk>
#include "monitor.h"
#include "descriptor_tables.h"
#include "console.h"
#include "paging.h"


int main(void)
{
    // Initialise all the ISRs and segmentation
    init_descriptor_tables();
    // asm volatile("int $0x3");
    // Initialise the screen (by clearing it)
    monitor_clear();
    // // Write out a sample string
    // monitor_write("Thanks, James Molloy!\n");

    // uartinit(); 
    // printk("Hello from C\n");

    // initialise_paging();

    monitor_write("Hello, paging world!\n");


    // asm volatile("int $0x3");
    // asm volatile("int $0x4");
    // asm("mov word [0xb8000], 0x0248");
    // asm volatile("mov word [0xb8000], 0x0248");

    return 0;
}
