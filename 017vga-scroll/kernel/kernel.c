#include "../drivers/screen.h"
# include "util.h"


void main() {
    clear_screen();
    // col, row
    // kprint_at("X", 1, 6);
    // kprint_at("This text spans multiple lines", 75, 10);
    // kprint_at("There is a line\nbreak", 0, 20);
    // kprint("There is a line\nbreak");
    // kprint_at("What happens when we run out of space?", 45, 24);

    // void kprint_at2(char *message, int row, int col, unsigned char fg, unsigned char bg)
    // kprint_at2("1. hello world", 3, 0, WHITE, BLUE);
    // kprint("\n");
    // kprint_at2("2. hello world", -1, -1, BLUE, WHITE);

     /* Fill up the screen */
    int i = 0;
    for (i = 0; i < 24; i++) {
        char str[255];
        int_to_ascii(i, str);
        // kprint_at(str, 0, i);
        kprint_at2(str, i, 0, WHITE, BLUE);
    }

    kprint_at("50This text forces the kernel to scroll. Row 0 will disappear. ", 50, 24);
    kprint("And with this text, the kernel will scroll again, and row 1 will disappear too!");
    
}
