### 0x00000083 32 big paging 4mb

```
 4MB pages and PAE paging disabled 下  page directory entity 的值为0x00000083 是什么含义
 在4MB页面和未启用PAE（Physical Address Extension）分页的情况下，一个Page Directory Entry（页目录项）的值为0x00000083表示如下含义：

31              12 11    9 8   7    6    5   4       3     2      1    0
+-----------------+---+---+----+----+----+------+-------+-----+------+
| Page Table Base | G | S | 0  | PCD | PWT | U/S | R/W | P | A | Reserved |
+-----------------+---+---+----+----+----+------+-------+-----+------+
| 0x000000        | 1 | 0 | 0  | 0   | 0   | 0    | 0   | 1 | 1 | 000    |
+-----------------+---+---+----+----+----+------+-------+-----+------+
具体每个字段的含义如下：

Page Table Base: 页面表基址，此处为0x000000。
G (Global): 全局位，此处为1，表示该页表不受全局刷新限制。
S (Size): 大小位，此处为0，表示该页目录项映射的是4KB页面而非4MB页面。
PCD (Page-level Cache Disable): 页级缓存禁用位，此处为0，表示对该页面的缓存策略没有禁用。
PWT (Page-level Write Through): 页级写透位，此处为0，表示对该页面采用写回策略。
U/S (User/Supervisor): 用户/特权位，此处为0，表示该页面只能由特权级代码进行访问。
R/W (Read/Write): 读/写位，此处为1，表示该页面可读写。
P (Present): 存在位，此处为1，表示该页目录项有效。
A (Accessed): 访问位，此处为1，表示该页面已被访问过。
Reserved: 保留位，此处为000，未使用。
综上所述，0x00000083表示的页目录项是指向一个4KB页面的有效项，该页面可以被特权级代码读写，并且已被访问过。这个页目录项没有启用全局刷新限制和页级缓存禁用，采用写回策略。

在使用4MB页面且PAE分页禁用的情况下，page directory entry的值为0x00000083，它表示页目录项的属性和地址。

具体来说，该值的含义如下：
- Bit 0-4：页表基址的高20位，表示页表的物理地址的高20位。
- Bit 5-7：保留位，必须为0。
- Bit 8：全局位（G），指示该页表项是否全局有效。
- Bit 9-11：保留位，必须为0。
- Bit 12-20：保留位，必须为0。
- Bit 21-31：保留位，必须为0。

因此，对于给定的0x00000083值，页表基址的高20位为0x00000，全局位为0，其余位必须为0。

需要注意的是，以上描述基于一般的x86体系结构，具体的处理器架构和操作系统可能会有所不同。


当禁用PAE (Physical Address Extension)分页且启用4MB页面时，Page Directory Entry（页目录项）的格式如下：

31              12 11    9 8   7    6    5   4       3     2      1    0
+-----------------+---+---+----+----+----+------+-------+-----+------+
| Page Table Base | G | S | 0  | PCD | PWT | U/S | R/W | P | A | Reserved |
+-----------------+---+---+----+----+----+------+-------+-----+------+
具体每个字段的含义如下：

Page Table Base: 页面表基址，指示了与该页目录项对应的页表在物理内存中的基址。
G (Global): 全局位，用于控制页表缓存（TLB）中的全局缓存设置。
S (Size): 大小位，用于标识该页目录项是否映射4MB大小的页面。
PCD (Page-level Cache Disable): 页级缓存禁用位，用于控制对该页面的缓存策略。
PWT (Page-level Write Through): 页级写透位，用于控制对该页面的写回策略。
U/S (User/Supervisor): 用户/特权位，用于控制页面的访问权限级别。
R/W (Read/Write): 读/写位，用于控制页面的读写权限。
P (Present): 存在位，用于标识该页目录项是否有效。
A (Accessed): 访问位，用于标识该页面是否被访问过。
Reserved: 保留位，未使用。
当启用4MB页面时，通过设置S位为1来指示该页目录项映射的是4MB页面。而禁用PAE分页，意味着物理地址的宽度限制在32位之内，因此不需要特殊处理物理地址的扩展。

```



### gdb
```
add-auto-load-safe-path /home/liikii/helloos/hello38/.gdbinit
add-auto-load-safe-path /home/liikii/helloos/029paging2/.gdbinit
set disassemble-next-line on
```

### gdb tutorial
```
https://users.cs.utah.edu/~aburtsev/238P/hw/hw4-boot-into-c/hw4-boot-into-c.html
```


### new vga address 
```
// Our kernel now loads at 0xC0000000, so what low memory address such as 0xb800 you used to access, should be LOAD_MEMORY_ADDRESS + 0xb800
#define LOAD_MEMORY_ADDRESS 0xC0000000
```


### pse bit in cr4 
```
PSE（Page Size Extension）位是CR4（Control Register 4）寄存器中的一个控制位，用于启用大页面大小的支持。

在x86架构中，通常将内存划分为固定大小的页面（Page），每个页面的大小为4KB。然而，通过启用PSE位，可以将页面的大小扩展为2MB或4MB，以提高内存管理的效率和性能。

当PSE位被设置为1时，即CR4寄存器的相应位被置位，处理器将识别和管理2MB或4MB大小的页面。这样，使用大页面的优势在于减少了页表的数量，从而降低了内存管理开销和TLB（Translation Lookaside Buffer）的缓存失效。

要注意的是，使用大页面也会带来一些限制和注意事项。例如，大页面只能对齐到相应页面大小的边界，且不能与小页面交错使用。因此，在启用PSE位之前，需要仔细考虑系统需求和内存管理方面的因素。

总结起来，PSE位是CR4寄存器中的一个控制位，用于启用大页面大小的支持。它可以提高内存管理的效率，但使用大页面时需要注意相关限制和注意事项。
```