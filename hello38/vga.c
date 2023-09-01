#include "vga.h"
#include "console.h"


unsigned short *VIDEO_MEM = (unsigned short*) 0xb8000;
unsigned short *VIDEO_PTR = (unsigned short*) 0xb8000;
char VIDEO_CLR = 0x7;

char DEF_COLOR = 0x7;

// int is_scrolled=0;
// int last_x=0, last_y=0;
int csr_x = 0, csr_y = 0;


/*
 * Change text colour
 */
void settextcolor(unsigned char forecolor, unsigned char backcolor)
{
    /* Top 4 bytes are the background, bottom 4 bytes
    *  are the foreground color */
    VIDEO_CLR = (backcolor << 4) | (forecolor & 0x0F);
}


/*
 * Needed to clear the screen
 */
void cls()
{
  int line, row;
  line = 0;
  row = 0;
  VIDEO_PTR = VIDEO_MEM;
  unsigned blank = 0x20 | (DEF_COLOR << 8);
  while(row < SCR_H){
    while(line < SCR_W){
      *VIDEO_PTR++ = blank;
      line++;
    }
    line=0;
    row++;    
  } 
  VIDEO_PTR = VIDEO_MEM;
}


void scroll(void)
{
    unsigned blank = 0x0;
    unsigned temp = 0x0;

    /* A blank is defined as a space... we need to give it
    *  backcolor too */
    blank = 0x20 | (DEF_COLOR << 8);

    /* Row 25 is the end, this means we need to scroll up */
    if(csr_y >= SCR_H)
    {
        /* Move the current text chunk that makes up the screen
        *  back in the buffer by a line */
        temp = csr_y - SCR_H + 1;
        memcpy (VIDEO_MEM, VIDEO_MEM + temp * SCR_W, (SCR_H - temp) * SCR_W * 2);

        /* Finally, we set the chunk of memory that occupies
        *  the last line of text to our 'blank' character */
        memsetw (VIDEO_MEM + (SCR_H - temp) * SCR_W, blank, SCR_W);
        csr_y = SCR_H - 1;
    }
}


void move_csr(void)
{
    unsigned temp;

    /* The equation for finding the index in a linear
    *  chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    temp = csr_y * 80 + csr_x;

    /* This sends a command to indicies 14 and 15 in the
    *  CRT Control Register of the VGA controller. These
    *  are the high and low bytes of the index that show
    *  where the hardware cursor is to be 'blinking'. To
    *  learn more, you should look up some VGA specific
    *  programming documents. A great start to graphics:
    *  http://www.brackeen.com/home/vga */
    outb(0x3D4, 14);
    outb(0x3D5, temp >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, temp);
}


/* Puts a single character on the screen */
void putchar(unsigned char c)
{
    unsigned short *where;
    unsigned att = VIDEO_CLR << 8;

    /* Handle a backspace, by moving the cursor back one space */
    if(c == 0x08)
    {
        if(csr_x != 0) csr_x--;
    }
    /* Handles a tab by incrementing the cursor's x, but only
    *  to a point that will make it divisible by 8 */
    else if(c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    /* Handles a 'Carriage Return', which simply brings the
    *  cursor back to the margin */
    else if(c == '\r')
    {
        csr_x = 0;
    }
    /* We handle our newlines the way DOS and the BIOS do: we
    *  treat it as if a 'CR' was also there, so we bring the
    *  cursor to the margin and we increment the 'y' value */
    else if(c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    /* Any character greater than and including a space, is a
    *  printable character. The equation for finding the index
    *  in a linear chunk of memory can be represented by:
    *  Index = [(y * width) + x] */
    else if(c >= ' ')
    {
        where = VIDEO_MEM + (csr_y * 80 + csr_x);
        *where = c | att; /* Character AND attributes: color */
        csr_x++;
    }

    /* If the cursor has reached the edge of the screen's width, we
    *  insert a new line in there */
    if(csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    /* Scroll the screen if needed, and finally move the cursor */
    scroll();
    move_csr();
}



/* Uses the above routine to output a string... */
void puts(unsigned char *text)
{
    int i;

    for (i = 0; i < strlen(text); i++)
    {
        putchar(text[i]);
    }

}


void kntohex(unsigned char *buffer, unsigned int decnum)
{
  int shift=0;
  unsigned int tempnum = decnum;

  while (tempnum>=16) {
    tempnum >>= 4;
    shift++;
  }

  for (; shift>=0; shift--) {
    tempnum = decnum;
    tempnum >>= (4*shift);
    tempnum &= 0xF;

    if (tempnum<10)
      *buffer++ = '0'+tempnum;
    else
      *buffer++ = 'A'+tempnum-10;
  }
  *buffer = '\0';
}


void put_dec(uint32_t n)
{

    if (n == 0)
    {
        putchar('0');
        return;
    }

    uint32_t acc = n;
    unsigned char c[32];
    int i = 0;
    while (acc > 0)
    {
        c[i] = '0' + acc%10;
        acc /= 10;
        i++;
    }
    c[i] = 0;

    unsigned char c2[32];
    c2[i--] = 0;
    int j = 0;
    while(i >= 0)
    {
        c2[i--] = c[j++];
    }
    puts(c2);
}

// void kputc(char c)
// {
//   unsigned att = VIDEO_CLR << 8;
//   *where = c | att;
// 	*VIDEO_PTR++ = c;
// 	*VIDEO_PTR++ = VIDEO_CLR;
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
// }

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

