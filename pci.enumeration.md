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