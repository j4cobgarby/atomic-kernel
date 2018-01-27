# Atomic kernel

My latest attempt at a kernel!

## Requirements, how to build, and how to use

### Requirements
#### For building
 - nasm assembler
 - i686-elf-gcc cross compiler
#### For emulating (optional, if you want to boot on real hardware)
 - qemu-system-i386

To get everything needed on Arch Linux, using trizen:
```
trizen -S qemu qemu-arch-extra nasm i686-elf-gcc i686-elf-binutils
```

### How to build
```
git clone https://github.com/j4cobgarby/atomic-kernel
cd atomic-kernel
make
```
and then to emulate on qemu
```
make run
```
### Usage
There's currently no usage instructions, because the user in fact can't do anything in the
operating system yet.

## Todo list

In no particular order, other than the order my brain thinks of them:

 - [ ] A userspace shell
 - [ ] A filesystem
 - [ ] A _verry_ rudimentary graphical system
 - [ ] A libc, to be used by all programs which need it
 - [ ] Running programs
 - [ ] Multiprocessing
