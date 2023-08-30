# compile
```
nasm -f bin hello.asm -o hello.bin
qemu-system-x86_64 hello.bin
```


## install i386 gcc
```
apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo 


export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf

cd dir_of_binutils-2.24.tar.gz
tar xf binutils-2.24.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.24/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log



cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-4.9.1/gcc-4.9.1.tar.bz2
tar xf gcc-4.9.1.tar.bz2
mkdir gcc-build
cd gcc-build
../gcc-4.9.1/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
sudo make all-gcc 
sudo make all-target-libgcc 
sudo make install-gcc 
sudo make install-target-libgcc 

```

#### test command
```
gcc -m32 -fno-pic -ffreestanding -c func.c -o func.o
objdump -d func.o
ld -o function.bin -m elf_i386 -Ttext 0x0 -N --oformat binary func.o
ndisasm -b 32 function.bin
```



