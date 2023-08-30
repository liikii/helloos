### info
```
introducing grub
```

### James Molloy's Tutorial Known Bugs
```
Problem: Interrupt handlers corrupt interrupted state
This article previously told you to know the ABI. If you do you will see a huge problem in the interrupt.s suggested by the tutorial: It breaks the ABI for structure passing! It creates an instance of the struct registers on the stack and then passes it by value to the isr_handler function and then assumes the structure is intact afterwards. However, the function parameters on the stack belongs to the function and it is allowed to trash these values as it sees fit (if you need to know whether the compiler actually does this, you are thinking the wrong way, but it actually does). There are two ways around this. The most practical method is to pass the structure as a pointer instead, which allows you to explicitly edit the register state when needed - very useful for system calls, without having the compiler randomly doing it for you. The compiler can still edit the pointer on the stack when it's not specifically needed. The second option is to make another copy the structure and pass that.

```



### section .bss  与  section .text
```
section .bss 和 section .text 是在汇编语言中用于定义不同类型数据和指令的节（section）。

section .bss：该节用于定义未初始化的全局变量和静态变量。BSS（Block Started by Symbol）意味着该节中的变量未被分配内存空间，而是在程序加载时自动分配。这些变量在程序运行前被初始化为零或空值。

section .text：该节用于定义可执行代码，即程序的实际指令部分。.text 节中包含了程序的逻辑和算法，以及函数和子程序的实现。这些指令在程序加载后会被加载到内存中，并按照程序流程进行执行。

总结区别：

.bss 区域用于存放未初始化的全局变量和静态变量，在程序运行前会被自动分配。
.text 区域用于存放程序的实际指令部分，包含可执行代码和函数的实现。
需要注意的是，上述的区别是基于常见的汇编语言约定，具体的汇编语言和平台可能会有所不同。
```



### grub magic number
```
Multiboot2 Specification version 2.0 
of Multiboot2 header
‘magic’
The field ‘magic’ is the magic number identifying the header, which must be the hexadecimal value 0xE85250D6.



Multiboot Specification version 0.6.96
3.1.2 The magic fields of Multiboot header
‘magic’
The field ‘magic’ is the magic number identifying the header, which must be the hexadecimal value 0x1BADB002.

‘flags’
The field ‘flags’ spec


```


### 
```
Now, we are copying 0x0248. Why this number? Well, it's in three parts:

┌───────background color
│ ┌─────foreground color
│ │ ┌─┬──letter, in ASCII
│ │ │ │
0 2 4 8
Let's start at the right. The last, two numbers are the letter, in ASCII. H is 72 in ASCII, and 48 is 72 in hexadecimal: (4 * 16) + 8 = 72. So this will write H.

| Value | Color          |
|-------|----------------|
| 0x0   | black          |
| 0x1   | blue           |
| 0x2   | green          |
| 0x3   | cyan           |
| 0x4   | red            |
| 0x5   | magenta        |
| 0x6   | brown          |
| 0x7   | gray           |
| 0x8   | dark gray      |
| 0x9   | bright blue    |
| 0xA   | bright green   |
| 0xB   | bright cyan    |
| 0xC   | bright red     |
| 0xD   | bright magenta |
| 0xE   | yellow         |
| 0xF   | white          |

```


### grub2-mkrescue
```
grub2-mkrescue 是一个用于创建 GRUB2 引导光盘或ISO映像文件的命令。它可以将 GRUB2 引导程序和相关文件打包成一个完整的引导映像，以便在计算机上进行引导。

以下是一个示例使用 grub2-mkrescue 命令创建引导映像的步骤：

1. 首先，确保你已经安装了 GRUB2 和相关工具。如果没有安装，你可以使用以下命令在 Ubuntu 上安装它：
   ```
   sudo apt-get install grub-pc-bin xorriso
   ```

2. 在命令行中，进入你的 GRUB2 配置文件所在的目录。通常情况下，该文件位于 /etc/grub.d/ 目录下。

3. 使用文本编辑器打开 grub.cfg 文件，这是 GRUB2 的配置文件。在其中添加或编辑引导菜单的配置项。你可以参考 GRUB2 的官方文档来了解如何配置菜单项。

4. 保存并关闭 grub.cfg 文件。

5. 运行以下命令来生成引导映像（光盘或ISO文件）：
   ```
   grub2-mkrescue -o output.iso
   ```
   其中，output.iso 是你希望生成的 ISO 文件的名称。

6. 稍等片刻，命令会将 GRUB2 引导程序和相关文件打包成一个 ISO 文件。

7. 生成完成后，你可以将生成的 ISO 文件刻录到光盘上，或使用虚拟机软件加载该 ISO 文件进行测试。

请注意，这只是一个基本的示例，你可以根据你的实际需求进行更多的配置和定制。确保在使用 grub2-mkrescue 命令之前，你已经正确配置了 GRUB2 的引导菜单。
```



### reference
```
https://users.cs.utah.edu/~aburtsev/238P/hw/hw4-boot-into-c/hw4-boot-into-c.html
```