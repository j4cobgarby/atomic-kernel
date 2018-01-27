#ifndef VGA_H
#define VGA_H

#include <stddef.h>
#include <stdint.h>
#include "cursor.h"
#include "system_constants.h"

extern volatile uint16_t* vga_buff;
extern int curr_col;
extern int curr_row;
extern uint8_t term_colour;

enum VGA_COLOUR {
	VGA_COLOUR_BLACK = 0,
	VGA_COLOUR_BLUE = 1,
	VGA_COLOUR_GREEN = 2,
	VGA_COLOUR_CYAN = 3,
	VGA_COLOUR_RED = 4,
	VGA_COLOUR_MAGENTA = 5,
	VGA_COLOUR_BROWN = 6,
	VGA_COLOUR_LIGHT_GREY = 7,
	VGA_COLOUR_DARK_GREY = 8,
	VGA_COLOUR_LIGHT_BLUE = 9,
	VGA_COLOUR_LIGHT_GREEN = 10,
	VGA_COLOUR_LIGHT_CYAN = 11,
	VGA_COLOUR_LIGHT_RED = 12,
	VGA_COLOUR_LIGHT_MAGENTA = 13,
	VGA_COLOUR_LIGHT_BROWN = 14,
	VGA_COLOUR_WHITE = 15,
};

static inline uint8_t make_vga_colour(enum VGA_COLOUR foreground, enum VGA_COLOUR background) {
     return background << 4 | foreground;
}

static inline uint16_t make_vga_entry(unsigned char cha, uint8_t colour) {
     return (uint16_t) colour << 8 | (uint16_t) cha;
}

void vga_clear();
void vga_putc(char c);
void vga_prints(const char* str);
void vga_setcolour(uint8_t colour);


#endif
