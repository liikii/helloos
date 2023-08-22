### check sig
```shell
wget https://ftp.gnu.org/gnu/gnu-keyring.gpg
wget wget https://mirrors.cloud.tencent.com/gnu/gdb/gdb-7.8.tar.gz
wget https://ftp.gnu.org/gnu/gdb/gdb-7.8.tar.gz.sig

gpg --verify --keyring ./gnu-keyring.gpg gcc-4.9.1.tar.bz2.sig gcc-4.9.1.tar.bz2
```



Check out the Makefile target `make debug`. This target uses builds `kernel.elf`, which
is an object file (not binary) with all the symbols we generated on the kernel, thanks to
the `-g` flag on gcc. Please examine it with `xxd` and you'll see some strings. Actually,
the correct way to examine the strings in an object file is by `strings kernel.elf`

We can take advantage of this cool qemu feature. Type `make debug` and, on the gdb shell:

- Set up a breakpoint in `kernel.c:main()`: `b main`
- Run the OS: `continue`
- Run two steps into the code: `next` then `next`. You will see that we are just about to set
  the 'X' on the screen, but it isn't there yet (check out the qemu screen)
- Let's see what's in the video memory: `print *video_memory`. There is the 'L' from "Landed in
  32-bit Protected Mode"
- Hmmm, let's make sure that `video_memory` points to the correct address: `print video_memory`
- `next` to put there our 'X'
- Let's make sure: `print *video_memory` and look at the qemu screen. It's definitely there.

Now is a good time to read some tutorial on `gdb` and learn super useful things like `info registers`
which will save us a lot of time in the future!


You may notice that, since this is a tutorial, we haven't yet discussed which kind
of kernel we will write. It will probably be a monolithic one since they are easier
to design and implement, and after all this is our first OS. Maybe in the future
we'll add a lesson "15-b" with a microkernel design. Who knows.