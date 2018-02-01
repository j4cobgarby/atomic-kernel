/* vga.c --- 
 * 
 * Filename: vga.c
 * Description: Implementations of some low-level vga functions
 * Author: Jacob Garby
 * URL: https://github.com/j4cobgarby/atomic-kernel/vga.c
 * 
 */

/* Code: */


#include "vga.h"

void vga_clear() {
    for (size_t index = 0; index < VGA_COLS * VGA_ROWS; index++) {
	// vga entries are of binary form BBBBFFFFCCCCCCCC
	// B is bg
	// F is fg
	// C is ascii
	vga_buff[index] = ((uint16_t) term_colour << 8) | ' ';
    }
}

void vga_putc(char c) {
    switch (c) {
    case '\n':
	{
	    if (curr_row + 1 < VGA_ROWS)
		curr_row++;
	    else {
		curr_row = 0;
		vga_clear();
	    }

	    // pass to next case to reset column and break
	}
    case '\r':
	{
	    curr_col = 0;
	    break;
	}
    default:
	{
	    const size_t putc_index = (VGA_COLS * curr_row) + curr_col;
	    vga_buff[putc_index] = ((uint16_t) term_colour << 8) | c;
	    if (curr_col + 1 < VGA_COLS)
		curr_col++;
	    else
		curr_col = 0;
	    if (curr_row + 1 >= VGA_ROWS)
		curr_row = 0;
	    break;
	}
    }
    update_cursor(curr_col, curr_row);
}

void vga_prints(const char *str) {
    for (size_t i = 0; str[i] != 0; i++) {
	vga_putc(str[i]);
    }
}

void vga_setcolour(uint8_t colour) {
    term_colour = colour;
}

/* vga.c ends here */
