#if !defined(__CONSOLE_H__)
#define __CONSOLE_H__

void uartinit(void); 
void printk(char *);

unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char data);

#endif
