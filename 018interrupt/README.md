### interrupt
```
一个中断请求（IRQ）是可编程中断控制器（PIC）发出的，PIC是为了中断CPU以执行中断服务程序（ISR）。ISR是处理由IRQ产生的数据的一个小程序，电脑中正在运行的处理会因为中断的产生而停止，直到ISR运行结束。
```


### idt
```
• Each interrupt/exception provided a number
• Number used to index into an Interrupt descriptor table
(IDT)
• IDT provides the entry point into a interrupt/exception
handler
• 0 to 255 vectors possible
– 0 to 31 used internally
– Remaining can be defined by the OS 
```



### xv6 idt 
```
• 0 to 31 reserved by Intel
• 32 to 63 used for hardware interrupts
T_IRQ0 = 32 (added to all hardware IRQs to
 scale them)
• 64 used for system call interrupt 

```



### idt
```
interrupt descriptor table
array of gate of interrupt
```

### gate of interrupt
```
address of segment desciptor and offset. isr
```


### isr
```
route 
interrupt handler
```



### gcc extended asm
```
asm asm-qualifiers ( AssemblerTemplate 
                 : OutputOperands 
                 [ : InputOperands
                 [ : Clobbers ] ])


asm asm-qualifiers ( AssemblerTemplate 
                      : OutputOperands
                      : InputOperands
                      : Clobbers
                      : GotoLabels)

constraint
A string constant specifying constraints on the placement of the operand; See Constraints for asm Operands, for details.

Output constraints must begin with either ‘=’ (a variable overwriting an existing value) or ‘+’ (when reading and writing). When using ‘=’, do not assume the location contains the existing value on entry to the asm, except when the operand is tied to an input; see Input Operands.

After the prefix, there must be one or more additional constraints (see Constraints for asm Operands) that describe where the value resides. Common constraints include ‘r’ for register and ‘m’ for memory. When you list more than one possible location (for example, "=rm"), the compiler chooses the most efficient one based on the current context. If you list as many alternates as the asm statement allows, you permit the optimizers to produce the best possible code. If you must use a specific register, but your Machine Constraints do not provide sufficient control to select the specific register you want, local register variables may provide a solution (see Specifying Registers for Local Variables).


在gcc的扩展汇编语法中，r和m是输入输出约束的一种形式。

r表示寄存器约束，用于指定某个操作数应该存放在一个寄存器中。例如，asm("mov %0, %%eax" : : "r"(value));表示将value存放在%eax寄存器中。
m表示内存约束，用于指定某个操作数应该存放在内存中。例如，asm("mov (%0), %%eax" : : "m"(address));表示将address指向的内存中的值存放在%eax寄存器中。
这些约束可以确保正确地将操作数加载到正确的位置，从而使内嵌汇编代码能够与C代码进行正确的交互。在编写内嵌汇编代码时，需要根据具体情况选择合适的约束类型。
```



### push error code
```
The special, CPU-dedicated interrupts are shown below.

0 - Division by zero exception
1 - Debug exception
2 - Non maskable interrupt
3 - Breakpoint exception
4 - 'Into detected overflow'
5 - Out of bounds exception
6 - Invalid opcode exception
7 - No coprocessor exception
8 - Double fault (pushes an error code)
9 - Coprocessor segment overrun
10 - Bad TSS (pushes an error code)
11 - Segment not present (pushes an error code)
12 - Stack fault (pushes an error code)
13 - General protection fault (pushes an error code)
14 - Page fault (pushes an error code)
15 - Unknown interrupt exception
16 - Coprocessor fault
17 - Alignment check exception
18 - Machine check exception
19-31 - Reserved
```


### isr 统一isr处理方法， 有的push err code, 有的不push 
```
hat's all gravy, but unfortunately, we have another problem - some interrupts also push an error code onto the stack. We can't call a common function without a common stack frame, so for those that don't push an error code, we push a dummy one, so the stack is the same.

[GLOBAL isr0]
isr0:
  cli                 ; Disable interrupts
  push byte 0         ; Push a dummy error code (if ISR0 doesn't push it's own error code)
  push byte 0         ; Push the interrupt number (0)
  jmp isr_common_stub ; Go to our common handler.
That sample routine will work, but 32 versions of that still sounds like a lot of code. We can use NASM's macro facility to cut this down, though:

%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
  [GLOBAL isr%1]        ; %1 accesses the first parameter.
  isr%1:
    cli
    push byte 0
    push byte %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  [GLOBAL isr%1]
  isr%1:
    cli
    push byte %1
    jmp isr_common_stub
%endmacro
We can now make a stub handler function just by doing

ISR_NOERRCODE 0
ISR_NOERRCODE 1
...
Much less work, and anything that makes our lives easier is worth doing. A quick look at the intel manual will tell you that only interrupts 8, 10-14 inclusive push error codes onto the stack. The rest require dummy error codes.
```



## qemu -d
```
在QEMU中，-d参数用于启用调试输出。guest_errors,int是该参数的一个值，表示启用针对虚拟机错误的调试输出，并将输出发送到标准错误流。

具体来说，guest_errors表示启用虚拟机中的错误调试输出。这将允许QEMU将虚拟机中的错误信息输出到标准错误流中，以便进行调试和故障排除。

int表示将调试输出以整数形式展示。这表示错误信息将以整数的形式显示，方便调试人员查看和分析。

使用-d guest_errors,int参数可以帮助开发人员在调试QEMU虚拟机时捕捉和分析错误。
```


### reference
```
http://www.cse.iitm.ac.in/~chester/courses/16o_os/slides/6_Interrupts.pdf
http://www.jamesmolloy.co.uk/tutorial_html/4.-The%20GDT%20and%20IDT.html
http://www.cse.iitm.ac.in/~chester/courses/16o_os/syllabus.html
```
