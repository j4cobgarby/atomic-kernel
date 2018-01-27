	FLAGS	equ 0x3
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
	;; functions defined in high level
	extern kernel_main
	extern enable_nmi
	extern disable_nmi
	
	global _start ; declare start as a function symbol with the given symbol size

_start:
	mov esp, stack_top	; set up stack - it grows downwards on x86
	
	;; in the future, initialise the processor state here. (GDT, paging, etc.)
	cli
	call disable_nmi
	lgdt [gdt_descript]

	;; enter protected mode, by setting protection enable bit in the control register 0 (cr0)
	mov eax, cr0
	or al, 1
	mov cr0, eax

	call reload_cs

	call enable_nmi
	sti
	
	call kernel_main

	;; computer has nothing left to do - put into infinite loop
	cli			; disable interrupts
	.hang:	hlt
	jmp .hang
	.end:
reload_cs:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
gdt_start:

	;; gdt entries go like this:

	;; bits		meaning
	;; ====================
	;; 0-15		limit of section, 0:15
	;; 16-32	base address, 0:15
	;; 32-39	more bits of the base address, 16:23
	;; 40-47	access byte (basically, the 'type')
	;; 48-51	more bits of the limit, 16:19
	;; 52-55	flags
	;; 56-63	last bits of the base, 24:31

	;; limit = 20 bits
	;; base = 32 bit

	;; access byte:
	;; ============
	;; 7	6  5	4	3	2	1	0
	;; Pr	Privl	'1'	Ex	DC	RW	Ac

	;; flags:
	;; ======
	;; 7	6	5	4
	;; Gr	Sz	0	0

	;; access:
	;; Pr = present bit, 1 for all valid sectors
	;; Privl = privilege, 2 bits - ring level, for security. 0 = kernel, 1 and 2 = device drivers, 3 = user apps
	;; Ex = executable? 1 for code, 0 for data
	;; DC = direction bit/conforming bit
	;; 	direction, for data: 0, segment grows up; 1, segment gros down (in which case offset > limit)
	;; 	conforming bit, for code:
	;; 		(read wiki.osdev.org/GDT for more info)
	;; RW = readable/writable
	;; 	for code; readable
	;; 	for data; writable
	;; Ac = set to 0, set to 1 automatically when accessed

	;; flags:
	;; Gr = granularity, 0 for byte granularity, 1 for 4KB granularity (pages) <- size of blocks
	;; Sz = size bit -- 0: 16 bit protected; 1: 32 bit protected
	
gdt_null:
	dd 0x0
	dd 0x0
gdt_cs:  			; KERNEL CODE:
	dw 0xffff		; limit 0:15
	dw 0x0000		; base  0:15
	db 0x0000		; base  16:23
	db 10011010b		; access
	db 11111100b		; limit 16:19 | flags
	db 0x0000		; base 24:32
gdt_ds:				; KERNEL DATA
	dw 0xffff
	dw 0x0000
	db 0x0000
	db 10010010b
	db 11111100b
	db 0x0000
gdt_end:			; addr. of end of gdt

gdt_descript:
	dw gdt_end - gdt_start - 1 ; size of gdt
	dd gdt_start

	;; addresses of gdt segs, relative to the start of the gdt
	CODE_SEG_ADDR equ gdt_cs - gdt_start
	DATA_SEG_ADDR equ gdt_ds - gdt_start
