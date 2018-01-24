// These two headers are provided by GCC itself, so no worry about not having them available
#include <stddef.h>
#include <stdint.h>

#include "VGA_constants.h"
#include "io.h"

#define VGA_COLS 80
#define VGA_ROWS 25

// This is the start of the vga text buffer. It's volatile because it can be changed
// by things outside of this program (by interrupts, etc.)
volatile uint16_t* vga_buff = (uint16_t*) 0xb8000;

int curr_col = 0;
int curr_row = 0;
uint8_t term_colour = 0x0f; // Black BG, White FG


void vga_clear() {
     for (size_t index = 0; index < VGA_COLS * VGA_ROWS; index++) {
	  // vga entries are of binary form BBBBFFFFCCCCCCCC
	  // B is bg
	  // F is fg
	  // C is ascii
	  vga_buff[index] = ((uint16_t)term_colour << 8) | ' ';
     }
}

void vga_putc(char c) {
     switch (c) {
     case '\n':
     {
	  if (curr_row+1 < VGA_ROWS) curr_row++;
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
	  vga_buff[putc_index] = ((uint16_t)term_colour << 8) | c;
	  if (curr_col+1 < VGA_COLS) curr_col++;
	  else curr_col = 0;
	  if (curr_row+1 >= VGA_ROWS) curr_row = 0;
	  break;
     }
     }
}

void vga_prints(const char* str) {
     for (size_t i = 0; str[i] != 0; i++) {
	  vga_putc(str[i]);
     }
}

void vga_setcolour(uint8_t colour) {
     term_colour = colour;
}

extern "C"
void kernel_main() {
     vga_clear();
     vga_prints("Hello, world!\n");
     vga_prints("This is the atomic kernel! > ");
}
