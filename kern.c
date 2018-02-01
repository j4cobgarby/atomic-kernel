/* kern.c --- 
 * 
 * Filename: kern.c
 * Description: High level entry point of the kernel.
 * Author: Jacob Garby
 * URL: https://github.com/j4cobgarby/atomic-kernel/kern.c
 * 
 */

/* Code: */


// These two headers are provided by GCC itself, so no worry about not having them available
#include <stddef.h>
#include <stdint.h>

#include "vga.h"
#include "system_constants.h"
#include "io.h"
#include "cursor.h"

extern void load_idt(unsigned long *idt_ptr);	// calls assembly to load idt from the given ptr

typedef struct idt_entry {
    unsigned short int offset_low;	// offset 0..15
    unsigned short int selector;	// code seg. selector in GDT (or LDT in future)
    unsigned char zero;		// just one byte, = 0
    unsigned char type_and_attributes;	// see below
    unsigned short int offset_high;	// offset 16..31
} idt_entry;

/* type_and_attributes
 *   7   6   5   4   3   2   1   0
 * +---+---+---+---+---+---+---+---+
 * |Prs|  DPL  | S | Gate Type     |
 * +---+---+---+---+---+---+---+---+
 *
 * Prs = presnt bit : 1 for all active interrupts
 * DPL = Descriptor privilege lvl
 * S = storage seg: 0 for interrupt and trap gates, see gate type
 * Gate Type = see below
 *
 * Gate types:
 * +--------+-----+------+----------------------------------+
 * | Binary | Hex | Dec. |           Description            |
 * +--------+-----+------+----------------------------------+
 * |   0101 | 0x5 |    5 | 80386 chip 32-bit TASK gate      |
 * |   0110 | 0x6 |    6 | 80286 chip 16-bit INTERRUPT gate |
 * |   0111 | 0x7 |    7 | 80286 chip 16-bit TRAP gate      |
 * |   1110 | 0xe |   14 | 80386 chip 32-bit INTERRUPT gate |
 * |   1111 | 0xf |   15 | 80386 chip 32-bit TRAP gate      |
 * +--------+-----+------+----------------------------------+ 
 */

idt_entry idt[256];		// 256 entries of the idt

void idt_init() {
    unsigned long idt_addr;
    unsigned long idt_ptr[2];

    // send words to IC (info about the ICWs here: http://www.brokenthorn.com/Resources/OSDevPic.html)
    outb(0x20, 0x11);
    outb(0xa0, 0x11);

    outb(0x21, 0x20);		// master pic vector offset
    outb(0xa1, 0x28);		// slave pic vector offset

    outb(0x21, 0x00);		// tell master that there's a slave at irq2
    outb(0xa1, 0x00);

    outb(0x21, 0x01);
    outb(0xa1, 0x01);

    // initialisation of PIC finished

    outb(0x21, 0xff);
    outb(0xa1, 0xff);

    idt_addr = (unsigned long) idt;
    idt_ptr[0] = (sizeof(idt_entry) * 256) + ((idt_addr & 0xffff) << 16);
    idt_ptr[1] = idt_addr >> 16;

    load_idt(idt_ptr);
}

// This is the start of the vga text buffer. It's volatile because it can be changed
// by things outside of this program (by interrupts, etc.)
volatile uint16_t *vga_buff = (uint16_t *) 0xb8000;

int curr_col = 0;
int curr_row = 0;
uint8_t term_colour = 0x0f;	// Black BG, White FG

////////////////////////////////////////////
// Enable/disable non-maskable interrupts //
////////////////////////////////////////////

void enable_nmi() {
    outb(0x70, inb(0x70) & 0x7f);
}

void disable_nmi() {
    outb(0x70, inb(0x70) & 0x80);
}

//
// VGA
//

void vga_clear_shift(int shift) {
    for (size_t index = 0; index < VGA_COLS * VGA_ROWS; index++) {
	term_colour =
	    ((((index + shift) % 16) + 1) << 4) | VGA_COLOUR_WHITE;
	vga_buff[index] = ((uint16_t) term_colour << 8) | ' ';
    }
}

void kernel_main() {
    /* uncomment me for fun rainbow thing
       for (int i = 0; 1; i = (i+1)%16) {
       vga_clear_shift(i);
       for (int x = 0; x < 20000; x++) {
       vga_buff[x%(VGA_COLS*VGA_ROWS)] = ((uint16_t)term_colour << 8) | ((x%79)+175);
       //vga_buff[x%VGA_COLS*VGA_ROWS] = ((uint16_t)term_colour<<8)|((x%3)+176);
       }
       }
     */
    idt_init();

    enable_cursor(0, 15);
    update_cursor(curr_col, curr_row);

    vga_clear();
    vga_prints("Welcome to The Atomic Kernel\n");
    vga_prints("VERSION ");
    vga_prints(ATOMIC_KERNEL_VERSION_STRING);

    while (1);
}

/* kern.c ends here */
