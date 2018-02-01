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
#include "idt.h"

// This is the start of the vga text buffer. It's volatile because it can be changed
// by things outside of this program (by interrupts, etc.)
volatile uint16_t *vga_buff = (uint16_t *) 0xb8000;

int curr_col = 0;
int curr_row = 0;
uint8_t term_colour = 0x0f;	// Black BG, White FG

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
