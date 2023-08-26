#ifndef PANIC_H
#define PANIC_H


#include "common.h"

void panic(char *message, char *file, u32int line);
void panic_assert(char *file, u32int line, char *desc);


#endif
