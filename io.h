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

#include <stdint.h>
#include <stddef.h>
#include "scancodes.h"

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void enable_nmi();
void disable_nmi();

#endif

/* io.h ends here */
