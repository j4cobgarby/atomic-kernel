all:
	nasm -felf32 boot.asm -o boot.o
	i686-elf-gcc -c kern.c -o kern.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c vga.c -o vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	i686-elf-gcc -ffreestanding -nostdlib -fno-use-linker-plugin -g -T linker.ld boot.o kern.o vga.o -o kern.elf -lgcc

run:
	qemu-system-i386 -kernel kern.elf
