#include "vga.h"


char *VIDEO_MEM = (char*) 0xb8000,
     *VIDEO_PTR = (char*) 0xb8000,
    VIDEO_CLR = 0x7;

// int is_scrolled=0;
// int last_x=0, last_y=0;


void _kputc(char c)
{
	*VIDEO_PTR++ = c;
	*VIDEO_PTR++ = VIDEO_CLR;
   /* Print a character on the screen*/
  // if (last_x && last_y) _kscrolldown ();
  // if(c=='\n')
  //     _knewline();
  //   else if(c=='\033') {
  //     asm("nop");
  //   } else if (c=='\t')
  //     _ktab();
  //   else if(c=='\b')
  //     _kbackspace();
  //   else if (c=='\r')
  //     _kminline();
  //   else {
// 		*VIDEO_PTR++ = c;
// 		*VIDEO_PTR++ = VIDEO_CLR;
  //   }
  // _kshiftAll();
  // _ksetcursauto();
}

/* void _kputc(char c)
{
   // Print a character on the screen
  // if (last_x && last_y) _kscrolldown ();
  if(c=='\n')
      _knewline();
    else if(c=='\033') {
      asm("nop");
    } else if (c=='\t')
      _ktab();
    else if(c=='\b')
      _kbackspace();
    else if (c=='\r')
      _kminline();
    else {
		*VIDEO_PTR++ = c;
		*VIDEO_PTR++ = VIDEO_CLR;
    }
  _kshiftAll();
  _ksetcursauto();
}
*/

