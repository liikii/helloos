Sure! Here's an example of kernel code in C for PCI device enumeration using ports 0xCF8 and 0xCFC:

```c
#include <stdio.h>
#include <stdint.h>

// Function to read a 32-bit value from a PCI configuration register
uint32_t pciConfigReadWord(uint8_t bus, uint8_t device, uint8_t function, uint8_t offset) {
    // Calculate the address for the configuration register
    uint32_t address = 0x80000000 | (bus << 16) | (device << 11) | (function << 8) | (offset & 0xFC);
    
    // Write the address to the configuration address port (0xCF8)
    outl(0xCF8, address);
    
    // Read and return the value from the configuration data port (0xCFC)
    return inl(0xCFC);
}

// Function to enumerate PCI devices and print their information
void enumeratePCIDevices() {
    uint8_t bus, device, function;
    
    for (bus = 0; bus < 256; bus++) {
        for (device = 0; device < 32; device++) {
            for (function = 0; function < 8; function++) {
                // Read the vendor ID and device ID
                uint32_t configData = pciConfigReadWord(bus, device, function, 0x00);
                uint16_t vendorID = configData & 0xFFFF;
                uint16_t deviceID = (configData >> 16) & 0xFFFF;
                
                // Check if the device exists
                if (vendorID != 0xFFFF) {
                    // Print the PCI device information
                    printf("Bus: %u, Device: %u, Function: %u\n", bus, device, function);
                    printf("Vendor ID: 0x%04X, Device ID: 0x%04X\n\n", vendorID, deviceID);
                }
            }
        }
    }
}

int main() {
    // Enumerate PCI devices
    enumeratePCIDevices();
    
    return 0;
}
```

This code defines two functions: `pciConfigReadWord` to read a 32-bit value from a PCI configuration register using ports 0xCF8 and 0xCFC, and `enumeratePCIDevices` to iterate through all possible PCI devices and print their vendor ID and device ID.

Note that this code assumes you have appropriate I/O port access permissions in your kernel environment. Also, you'll need to define the `inl` and `outl` functions to read from and write to I/O ports respectively, as they are architecture-specific and not provided in standard C libraries.

Please make sure to adapt this code to your specific kernel environment and hardware setup as needed.


```c
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>

const u32 PCI_ENABLE_BIT     = 0x80000000;
const u32 PCI_CONFIG_ADDRESS = 0xCF8;
const u32 PCI_CONFIG_DATA    = 0xCFC;

// func - 0-7
// slot - 0-31
// bus - 0-255
u32 r_pci_32(u8 bus, u8 device, u8 func, u8 pcireg) {
        // unsigned long flags;
        // local_irq_save(flags)

        outl(PCI_ENABLE_BIT | (bus << 16) | (device << 11) | (func << 8) | (pcireg << 2), PCI_CONFIG_ADDRESS);
        u32 ret = inl(PCI_CONFIG_DATA);

        // local_irq_restore(flags);
        return ret;
}

static __init int init_pcilist(void) {
        u8 bus, device, func;
        u32 data;

        for(bus = 0; bus != 0xff; bus++) {
                for(device = 0; device < 32; device++) {
                        for(func = 0; func < 8; func++) {
                                data = r_pci_32(bus, device, func, 0);

                                if(data != 0xffffffff) {
                                        printk(KERN_INFO "bus %d, device %d, func %d: vendor=0x%08x\n", bus, device, func, data);
                                }
                        }
                }
        }
        return 0;
}

static __exit void exit_pcilist(void) {
        return;
}

module_init(init_pcilist);
module_exit(exit_pcilist);
```



Software implementation
Configuration reads and writes can be initiated from the CPU in two ways: one legacy method via I/O addresses 0xCF8 and 0xCFC, and another called memory-mapped configuration.[3]

The legacy method was present in the original PCI, and it is called Configuration Access Mechanism (CAM). It allows for 256 bytes of a device's address space to be reached indirectly via two 32-bit registers called PCI CONFIG_ADDRESS and PCI CONFIG_DATA. These registers are at addresses 0xCF8 and 0xCFC in the x86 I/O address space.[4] For example, a software driver (firmware, OS kernel or kernel driver) can use these registers to configure a PCI device by writing the address of the device's register into CONFIG_ADDRESS, and by putting the data that is supposed to be written to the device into CONFIG_DATA. Since this process requires a write to a register in order to write the device's register, it is referred to as "indirection".

The format of CONFIG_ADDRESS is the following:

0x80000000 | bus << 16 | device << 11 | function <<  8 | offset




Each PCI bus have devices attached and each device have functions. The topology for PCI bus looks like this:

Upto 256 Bus
Each bus have maximum 32 devices attached
Each device have atmost 8 functions
Buses are connected using Bridges


在szhou42/osdev项目中，pci_size_map是一个用于映射PCI设备配置空间大小的数组。该数组定义了每个PCI设备类型所需的配置空间大小，以字节为单位。配置空间包含了设备的寄存器、寄存器集合和其他相关信息。

PCI设备配置空间是由PCI规范定义的，它包含了设备的基本信息、设备寄存器和设备的功能描述等。对于每个PCI设备，系统都会从其配置空间中读取必要的信息以进行正确的初始化和驱动。

pci_size_map数组的索引对应于设备的类别代码（Class Code），而数组的值对应于该设备类别所需的配置空间大小。通过查询pci_size_map数组，操作系统可以根据设备的类别代码确定设备的配置空间大小。

这个pci_size_map数组在操作系统开发中特别有用，因为它提供了一种方便的方式来确定每个PCI设备所需的配置空间大小，从而可以在系统初始化过程中正确地分配和管理资源。

总之，pci_size_map定义了每个PCI设备类型所需的配置空间大小，帮助操作系统正确地分配和管理设备资源。



LINUX DEVICE DRIVERS

LINUX
DEVICE
DRIVERS


### ata 
```
Short for Advanced Technology Attachment, ATA was approved on May 12, 1994, and is an interface that connects hard drives, CD-ROM (compact disc read-only memory) drives, and other drives. The first ATA interface is now commonly called PATA, which is short for Parallel AT Attachment after the introduction of SATA (Serial AT Attachment). Today, almost all home computers use the ATA interface, including Apple computers, which use SATA.
```


### github 里 szhou42/osdev 项目里 ata_init 函数的作用
```
在szhou42/osdev项目中，ata_init函数是用于初始化ATA（Advanced Technology Attachment）硬盘驱动的函数。

ATA是一种常见的硬盘接口标准，用于连接计算机主板和硬盘。ata_init函数的作用是在操作系统启动时初始化ATA硬盘驱动，以便后续能够正确地读取和写入硬盘数据。

具体而言，ata_init函数可能会执行以下一些任务：

1. 检测ATA控制器：函数会检测系统中存在的ATA控制器，并确定其I/O端口和中断线路。

2. 识别连接的硬盘：函数会与每个ATA控制器通信，发送命令以识别连接的硬盘。这个过程称为ATA设备识别（ATA device identification）。通过识别硬盘，操作系统可以获取硬盘的参数信息，如容量、扇区大小等。

3. 初始化ATA驱动：函数会根据识别到的硬盘信息，初始化ATA硬盘驱动程序的数据结构和状态。这样操作系统就可以利用驱动程序来进行硬盘读写操作。

4. 分配资源：根据硬盘数量和配置，函数可能会分配适当的内存和其他资源来管理和操作硬盘。

总之，ata_init函数的作用是在操作系统启动时，对ATA硬盘驱动进行初始化，包括探测ATA控制器、识别连接的硬盘、初始化驱动程序等。这样操作系统就能够正确地与硬盘进行数据交互，并实现文件系统的读写功能。
```



### sata primary drive secondary drive
```
SATA (Serial ATA) is a computer bus interface that connects storage devices such as hard drives and solid-state drives (SSDs) to the motherboard of a computer. The terms "primary drive" and "secondary drive" refer to the different SATA connections available on a motherboard.

Typically, a motherboard will have multiple SATA ports to which you can connect SATA drives. The primary drive is usually connected to the SATA port labeled "SATA1" or "SATA0". This is the main drive that contains the operating system and other critical files.

The secondary drive, on the other hand, is connected to another available SATA port, usually labeled "SATA2", "SATA3", and so on. This drive can be used for additional storage, such as storing personal files, media, or backup data.

It's important to note that the terms "primary" and "secondary" are not fixed and can vary depending on the motherboard manufacturer. Some motherboards may use different naming conventions, such as "Primary Master" and "Primary Slave" for older IDE (Integrated Drive Electronics) connections.

If you have any specific questions or need further clarification, please let me know!
```



### Tom Shanley, Protected Mode Software Architecture, Addison-Wesley (1996), 



Master和Slave分别是“主”和“从”的意思。早期主板只支持并口（ATA）硬盘和光驱，板上标配2个ATA插槽，每个插槽可以用同一条数据线连接2个并口设备，这2个设备之间就要通过设置“主”和“从”来区别，即一个设备是Master，则另一个必须是Slave，反之亦然，否则就会发生冲突。这个都是在硬盘和光驱上通过跳线来实现的，设备上会用Master和Slave标注跳线的接法。
