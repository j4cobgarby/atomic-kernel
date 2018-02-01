#include "idt.h"

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
