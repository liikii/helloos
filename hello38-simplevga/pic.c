#include "pic.h"
#include "system.h"
/*
 * PIC is very complex, for a better understanding, visist
 * http://www.brokenthorn.com/Resources/OSDevPic.html
 * */
void pic_remap() 
{   
    // Remap the PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    // irq 0 to 7 is mapped to 0x20 to 0x27, irq 8 to F is mapped to 28 to 2F
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    // connect master pic with slave pic
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    // set x86 mode
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    // clear the mask register
    outb(0x21, 0x0);
    outb(0xA1, 0x0); 
}


/*
 * Tell PIC interrupt is handled
 * */
void irq_ack(uint8_t irq) 
{
    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    if(irq >= 0x28)
        outb(PIC2, PIC_EOI);
    /* In either case, we need to send an EOI to the master
    *  interrupt controller too */
    outb(PIC1, PIC_EOI);
}
