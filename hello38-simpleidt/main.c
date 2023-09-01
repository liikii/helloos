#include "console.h"
#include "vga.h"
#include "idt.h"


// static inline void lcr3(unsigned int val){
//     asm volatile("movl %0,%%cr3" : : "r" (val));
// }
static inline void halt(void){
    asm volatile("hlt" : : );
}


int main(void){
    // int i;
    // int sum = 0;
    // // Initialize the console
    uartinit(); 
    printk("Hello from C\n");
    // // Create your page table here
    // // lcr3(ptd_address);
    // for (i = 0; i < 32 /*64*/; i++) {
    //     int *p = (int *)(i * 4096 * 32);
    //     sum += *p; 
    //     printk("page\n"); 
    // }
    // char* video_memory = (char*) 0xb8000;
    // *video_memory = 'H';
    cls();
    putchar('A');
    putchar('B');
    putchar('C');
    putchar('\n');
    // puts((unsigned char *)"DEF");
    // kntohex
    // unsigned char *abc = "helloworld";
    // unsigned char abc[10];
    // kntohex(abc, 12);
    // puts(abc);

    idt_init();

    puts((unsigned char *)"123");
    // __asm__ __volatile__("int $0x3");
    __asm__ __volatile__("int $0x3");
    halt();
    return 0; 
}
