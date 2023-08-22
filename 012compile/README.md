#### test command
```
gcc -m32 -fno-pic -ffreestanding -c func.c -o func.o
objdump -d func.o
ld -o function.bin -m elf_i386 -Ttext 0x0 -N --oformat binary func.o
ndisasm -b 32 function.bin
```



#### foo compile
```shell




gcc -m32 -ffreestanding -c filename.c -o out.o

gcc -ffreestanding  -O -nostdinc -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer  -fno-stack-protector

gcc -O -nostdinc -fno-pic -static -fno-builtin -fno-strict-aliasing -O2 -Wall -MD -ggdb -m32 -Werror -fno-omit-frame-pointer  -fno-stack-protector -c 


ld -o function.bin -m elf_i386 -Ttext 0x0 --oformat binary func2.o
```

gcc参数
```text
    -c     Compile or assemble the source files, but do not link.  The
           linking stage simply is not done.  The ultimate output is in
           the form of an object file for each source file.

           By default, the object file name for a source file is made by
           replacing the suffix .c, .i, .s, etc., with .o.

           Unrecognized input files, not requiring compilation or
           assembly, are ignored.

    -ggdb
        Produce debugging information for use by GDB.  This means to
        use the most expressive format available (DWARF, stabs, or
        the native format if neither of those are supported),
        including GDB extensions if at all possible.



    -O2 Optimize even more.  GCC performs nearly all supported
               optimizations that do not involve a space-speed tradeoff.  As
               compared to -O, this option increases both compilation time
               and the performance of the generated code.

               -O2 turns on all optimization flags specified by -O.  It also
               turns on the following optimization flags:


    -static
       On systems that support dynamic linking, this overrides -pie
       and prevents linking with the shared libraries.  On other
       systems, this option has no effect.


  -O
       -O1 Optimize.  Optimizing compilation takes somewhat more time,
           and a lot more memory for a large function.

           With -O, the compiler tries to reduce code size and execution
           time, without performing any optimizations that take a great
           deal of compilation time.

           -O turns on the following optimization flags:

           -fauto-inc-dec -fbranch-count-reg -fcombine-stack-adjustments
           -fcompare-elim -fcprop-registers -fdce -fdefer-pop
           -fdelayed-branch -fdse -fforward-propagate
           -fguess-branch-probability -fif-conversion -fif-conversion2
           -finline-functions-called-once -fipa-profile -fipa-pure-const
           -fipa-reference -fipa-reference-addressable -fmerge-constants
           -fmove-loop-invariants -fomit-frame-pointer -freorder-blocks
           -fshrink-wrap -fshrink-wrap-separate -fsplit-wide-types
           -fssa-backprop -fssa-phiopt -ftree-bit-ccp -ftree-ccp
           -ftree-ch -ftree-coalesce-vars -ftree-copy-prop -ftree-dce
           -ftree-dominator-opts -ftree-dse -ftree-forwprop -ftree-fre
           -ftree-phiprop -ftree-pta -ftree-scev-cprop -ftree-sink
           -ftree-slsr -ftree-sra -ftree-ter -funit-at-a-time

    -nostdinc
           Do not search the standard system directories for header
           files.  Only the directories explicitly specified with -I,
           -iquote, -isystem, and/or -idirafter options (and the
           directory of the current file, if appropriate) are searched.


    -MD -MD is equivalent to -M -MF file, except that -E is not
           implied.  The driver determines file based on whether an -o
           option is given.  If it is, the driver uses its argument but
           with a suffix of .d, otherwise it takes the name of the input
           file, removes any directory components and suffix, and
           applies a .d suffix.

           If -MD is used in conjunction with -E, any -o switch is
           understood to specify the dependency output file, but if used
           without -E, each -o is understood to specify a target object
           file.

           Since -E is not implied, -MD can be used to generate a
           dependency output file as a side effect of the compilation
           process.

```


### objdump参数
```

 -d
       --disassemble
       --disassemble=symbol
           Display the assembler mnemonics for the machine instructions
           from the input file.  This option only disassembles those
           sections which are expected to contain instructions.  If the
           optional symbol argument is given, then display the assembler
           mnemonics starting at symbol.  If symbol is a function name
           then disassembly will stop at the end of the function,
           otherwise it will stop when the next symbol is encountered.
           If there are no matches for symbol then nothing will be
           displayed.

           Note if the --dwarf=follow-links option is enabled then any
           symbol tables in linked debug info files will be read in and
           used when disassembling.

```


gcc parameter2
```
3.3 Compiling C Code
When compiling the C code for the OS, a lot of flags to GCC need to be used. This is because the C code should not assume the presence of a standard library, since there is no standard library available for our OS. For more information about the flags, see the GCC manual.

The flags used for compiling the C code are:

    -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs
As always when writing C programs we recommend turning on all warnings and treat warnings as errors:

    -Wall -Wextra -Werror
You can now create a function kmain in a file called kmain.c that you call from loader.s. At this point, kmain probably won’t need any arguments (but in later chapters it will).
```


ld -m elf_i386 -s -o file file.o




gcc -m32 -fno-pic -ffreestanding -c func.c -o func2.o

gcc -m32 -fno-pic -ffreestanding -c func.c -o func2.o




gcc -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -ffreestanding  -c func.c -o func2.o


gcc -m32 -fno-pic -ffreestanding -c pointer.c -o pointer.o



gcc -m32 -fno-pic -ffreestanding -fno-strength-reduce -c func.c -o func.o

gcc -m32 -fno-pic -ffreestanding -fno-strength-reduce -c pointer.c -o pointer.o
-fno-strength-reduce