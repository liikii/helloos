// #include "console.h"

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
    // uartinit(); 
    // printk("Hello from C\n");
    // // Create your page table here
    // // lcr3(ptd_address);
    // for (i = 0; i < 32 /*64*/; i++) {
    //     int *p = (int *)(i * 4096 * 32);
    //     sum += *p; 
    //     printk("page\n"); 
    // }
    // asm volatile("mov $3, %eax\n");
    char* video_memory = (char*) 0xb8000;
    // *video_memory = 'H';
    video_memory[0] = 'X'; 
    video_memory[1] = 0x0f; /* White text on black background */

    video_memory = (char*) (0xC0000000 + 0xb8000);
    // *video_memory = 'H';
    video_memory[2] = 'F'; 
    video_memory[3] = 0x1f; /* White text on blue background */

    halt();
    return 0; 
}
