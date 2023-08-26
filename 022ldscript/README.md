

## change kernel entry to _start compared to section 13
```
Modify kernel/kernel.c and change main() to kernel_main() since gcc recognizes "main" as a special keyword and we don't want to mess with that.

Change boot/kernel_entry.asm to point to the new name accordingly.

To fix the i386-elf-ld: warning: cannot find entry symbol _start; defaulting to 0000000000001000 warning message, add a global _start; and define the _start: label in boot/kernel_entry.asm.
```


---



## 注意
```
因为16位下, 内存有限制, 无法把kernel写到 1MB 的位置, 放弃在原先基础上改动. 准备引用grub
```