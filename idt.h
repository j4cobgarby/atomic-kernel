#ifndef IDT_H
#define IDT_H

#include <stddef.h>
#include <stdint.h>

#include "io.h"

extern void load_idt(unsigned long *idt_ptr);

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

void idt_init();

#endif
