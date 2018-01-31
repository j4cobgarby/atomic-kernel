# Atomic kernel

My latest attempt at a kernel!

## Requirements, how to build, and how to use

### Requirements
#### For building
 - nasm assembler
 - i686-elf-gcc cross compiler (any one will do, probably, but it seems that the one provided on the AUR doesn't work.)

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
There's currently no usage instructions, because the user in fact can't do anything at this point in time.

## Todo list

In no particular order, other than the order my brain thinks of them:

 - [ ] A userspace shell
 - [ ] A filesystem
 - [ ] A _verry_ rudimentary graphical system
 - [ ] A libc, to be used by all programs which need it
 - [ ] Running programs
 - [ ] Multiprocessing
