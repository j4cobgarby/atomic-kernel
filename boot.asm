	FLAGS	equ (1<<0) | (1<<1)
	MAGIC	equ 0x1BADB002
	CHECKSUM equ -(FLAGS + MAGIC) ; (FLAGS + MAGIC) + CHECKSUM must equal zero.

	;; define the actual multiboot header. grub will search for this in the first 8KB
	;; the linker will make sure this is in the first 8KB
	section .multiboot
	align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

	section .bss
	align 16
stack_bot:	resb 16384	; 16KB stack
stack_top:

	;; entry point of kernel
	section .text
	global _start ; declare start as a function symbol with the given symbol size
_start:
	mov esp, stack_top	; set up stack - it grows downwards on x86

	;; in the future, initialise the processor state here. (GDT, paging, etc.)

	;; this is defined in C - calls the high level kernel
	extern kernel_main
	call kernel_main

	;; computer has nothing left to do - put into infinite loop
	cli			; disable interrupts
	.hang:	hlt
	jmp .hang
	.end:
