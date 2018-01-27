/* cursor.h --- 
 * 
 * Filename: cursor.h
 * Description: Various inline functions to modify the state of the kernel in the vga textmode
 * Author: Jacob Garby
 * URL: https://github.com/j4cobgarby/atomic-kernel/cursor.h
 * 
 */

/* Code: */


#ifndef CURSOR_H
#define CURSOR_H

#include "system_constants.h"
#include "io.h"
#include "vga.h"

static inline void update_cursor(int x, int y) {
     uint16_t pos = y * VGA_COLS + x;
     outb(0x3d4, 0x0f);
     outb(0x3d5, (uint8_t) (pos & 0xff));
     outb(0x3d4, 0x0e);
     outb(0x3d5, (uint8_t) ((pos >> 8) & 0xff));
}

static inline void disable_cursor() {
     outb(0x3d4, 0x0a);
     outb(0x3d5, 0x20);
}

static inline void enable_cursor(uint8_t cursor_start, uint8_t cursor_end) {
     outb(0x3d4, 0x0a);
     outb(0x3d5, (inb(0x3d5) & 0xc0) | cursor_start);
 
     outb(0x3d4, 0x0b);
     outb(0x3d5, (inb(0x3e0) & 0xe0) | cursor_end);
}

#endif

/* cursor.h ends here */
