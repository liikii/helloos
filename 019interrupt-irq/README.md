## isr irq


### irq line sharing
```
I/O Interrupt Handling
In general, an I/O interrupt handler must be flexible enough to service several devices at the same time. In the PCI bus architecture, for instance, several devices may share the same IRQ line. This means that the interrupt vector alone does not tell the whole story. In the example shown in Table 4-3, the same vector 43 is assigned to the USB port and to the sound card. However, some hardware devices found in older PC architectures (such as ISA) do not reliably operate if their IRQ line is shared with other devices.

Interrupt handler flexibility is achieved in two distinct ways, as discussed in the following list.

```



### reference
```
Understanding the Linux Kernel, 3rd Edition by Interrupt Handling
https://www.oreilly.com/library/view/understanding-the-linux/0596005652/ch04s06.html

Interrupt Sharing and Interrupt Conflicts
https://tldp.org/HOWTO/Plug-and-Play-HOWTO-10.html
```


### irq remapping
```
This is almost certainly an x86 question, especially given the numbers you mentioned. <P>The mapping between hardware IRQ and software INT is programmed into the interrupt controller. If you are writing your own OS, you'd have an interrupt controller driver that did this. That driver would have to be aware of the several different types of IRQ controllers. Some machines in fact have more than one controller (newer ones are called Advanced I/O PICs, or IOAPICs for short. Older ones are just called PICs).<P>Most IRQ sharing occurs because multiple devices are connected to the same IRQ line. A standard PIC only has 16 of these, leading to the 16 interrupts we're all used to on an x86. Newer machines have IOAPICs, which have somewhere around 30 inputs. <P>Anyway, if you intend to do this on an OS, the OS must be aware that the hardware IRQ's are going to end up somewhere else. If I remember right, MSDOS left the PIC alone, so it got the default BIOS configuration (IRQ 0-7 --> INT 8-F, IRQ 8-F --> INT 70-77). Windows 9x assumed everything was a normal PIC and remapped the DOS settings (IRQ 0-F --> 50-5F). It did this because software INTs 8-1F are Intel processor events, and overlapping them with hardware IRQ's was a dumb idea (blame IBM for that one). WinNT remaps things starting at 30 and going up, so IRQ 0-F --> 30-3F on a standard PIC machine, and 30-4F or so on machines with IOAPIC's (which are required for dual procs)


Protected Mode
In protected mode, the IRQs 0 to 7 conflict with the CPU exception which are reserved by Intel up until 0x1F. (It was an IBM design mistake.) Consequently it is difficult to tell the difference between an IRQ or an software error. It is thus recommended to change the PIC's offsets (also known as remapping the PIC) so that IRQs use non-reserved vectors. A common choice is to move them to the beginning of the available range (IRQs 0..0xF -> INT 0x20..0x2F). For that, we need to set the master PIC's offset to 0x20 and the slave's to 0x28. For code examples, see below.
```


### PIC remapping
```
The PICs are communicated with via the I/O bus. Each has a command port and a data port:

Master - command: 0x20, data: 0x21
Slave - command: 0xA0, data: 0xA1
The code for remapping the PICs is the most difficult and obfusticated. To remap them, you have to do a full reinitialisation of them, which is why the code is so long. If you're interested in what's actually happening, there is a nice description here.

https://wiki.osdev.org/PIC
```