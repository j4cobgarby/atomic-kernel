CC=i686-elf-gcc
LD=${CC}
NASM_ASSEMBLER=nasm

CC_FLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
NASM_FLAGS=-felf32
LD_FLAGS=-ffreestanding -nostdlib -fno-use-linker-plugin -g

all:
	mkdir -p build dist

	${NASM_ASSEMBLER} ${NASM_FLAGS} boot.asm -o build/boot.o
	${CC} -c kern.c -o build/kern.o ${CC_FLAGS}
	${CC} -c vga.c -o build/vga.o ${CC_FLAGS}

	${LD} ${LD_FLAGS} -T linker.ld build/boot.o build/kern.o build/vga.o -o dist/kern.elf -lgcc

run:
	qemu-system-i386 -kernel dist/kern.elf
