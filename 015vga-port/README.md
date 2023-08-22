### vga
```
The text write console is performed by the frame buffer is completed by the I / O map of memory. The starting address of the memory mapping I / O of the frame buffer is 0x000b8000.The memory is divided into 16-bit unit, 16 bits determine characters, foreground, and background colors. The highest eight is the character’s ASCII value, bit 7–4 is the background, bit 3–0 is the foreground, as can be seen in the following figure:
```


### cursor description and data
```
Moving the cursor of the framebuffer is done via two different I/O ports. The cursor’s position is determined with a 16 bits integer: 0 means row zero, column zero; 1 means row zero, column one; 80 means row one, column zero and so on. Since the position is 16 bits large, and the out assembly code instruction argument is 8 bits, the position must be sent in two turns, first 8 bits then the next 8 bits. The framebuffer has two I/O ports, one for accepting the data, and one for describing the data being received. Port 0x3D4 is the port that describes the data and port 0x3D5 is for the data itself.

To set the cursor at row one, column zero (position 80 = 0x0050), one would use the following assembly code instructions:
```

```
out 0x3D4, 14           ; 14 tells the framebuffer to expect the highest 8 bits of the position
out 0x3D5, 0x00         ; sending the highest 8 bits of 0x0050
out 0x3D4, 15           ; 15 tells the framebuffer to expect the lowest 8 bits of the position
out 0x3D5, 0x50         ; sending the lowest 8 bits of 0x0050
```




```
  global inb

    ; inb - returns a byte from the given I/O port
    ; stack: [esp + 4] The address of the I/O port
    ;        [esp    ] The return address
    
    inb:
        mov dx, [esp + 4]       ; move the address of the I/O port to the dx register
        in  al, dx              ; read a byte from the I/O port and store it in the al register
        ret                     ; return the read byte
```


```
   global outb             ; make the label outb visible outside this file

    ; outb - send a byte to an I/O port
    ; stack: [esp + 8] the data byte
    ;        [esp + 4] the I/O port
    ;        [esp    ] return address
    
    outb:
        mov al, [esp + 8]    ; move the data to be sent into the al register
        mov dx, [esp + 4]    ; move the address of the I/O port into the dx register
        out dx, al           ; send the data to the I/O port
        ret                  ; return to the calling function

```


### test
```
    * Now you can examine both variables using gdb, since we still
    * don't know how to print strings on screen. Run 'make debug' and
    * on the gdb console:
    * breakpoint kernel.c:21
    * continue
    * print position
    * print offset_from_vga
```