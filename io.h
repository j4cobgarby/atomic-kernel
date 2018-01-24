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

////////////////////////////////////////////
// Enable/disable non-maskable interrupts //
////////////////////////////////////////////

extern "C"
static void enable_nmi() {
     outb(0x70, inb(0x70)&0x7f);
}

extern "C"
static void disable_nmi() {
     outb(0x70, inb(0x70)&0x80);
}

// Enable/disable interrupts

static void enable_interrupts() {
     asm("sti");
}

static void disable_interrupts() {
     asm("cli");
}


#endif
