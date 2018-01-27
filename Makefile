all:
	mkdir -p build dist

	nasm -felf32 boot.asm -o build/boot.o
	i686-elf-gcc -c kern.c -o build/kern.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	i686-elf-gcc -c vga.c -o build/vga.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

	i686-elf-gcc -ffreestanding -nostdlib -fno-use-linker-plugin -g -T linker.ld build/boot.o build/kern.o build/vga.o -o dist/kern.elf -lgcc

run:
	qemu-system-i386 -kernel dist/kern.elf -soundhw pcspk
