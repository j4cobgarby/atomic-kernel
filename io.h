/* io.h --- 
 * 
 * Filename: io.h
 * Description: Functions to read/write to/from hardware I/O ports
 * Author: Jacob Garby
 * URL: https://github.com/j4cobgarby/atomic-kernel/io.h
 * 
 */

/* Code: */


#ifndef IO_H
#define IO_H

#include "scancodes.h"

// Writes to an io port
static inline void outb(uint16_t port, uint8_t val) {
     asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

// Reads an io port and returns the result
static inline uint8_t inb(uint16_t port) {
     uint8_t ret;
     asm volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
     return ret;
}

#endif

/* io.h ends here */
