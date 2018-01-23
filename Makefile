all:
	nasm -felf32 boot.asm -o boot.o
	i686-elf-g++ -c kern.cpp -o kern.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

	i686-elf-gcc -ffreestanding -nostdlib -fno-use-linker-plugin -g -T linker.ld boot.o kern.o -o kern.elf -lgcc

run:
	qemu-system-i386 -kernel kern.elf &> /dev/null
