ENTRY(_start)

SECTIONS {
	 /* Start kernel at 1M, because below 1M is used for x86 things */
	 . = 1M;

	 /* Multiboot spec. header goes first */
	 /* rodata means Read Only */
	 .rodata BLOCK(4K) : ALIGN(4K) {
	 	 *(.multiboot)
	 }

	 /* Code */
	 .text BLOCK(4K) : ALIGN(4K) {
	       *(.text)
	 }

	 .rodata BLOCK(4K) : ALIGN(4K) {
	 	 *(.rodata)
	 }

	 .data BLOCK(4K) : ALIGN(4K) {
	       *(.data)
	 }

	 .bss BLOCK(4K) : ALIGN(4K) {
	      *(COMMON)
	      *(.bss)
	 }
}
