//
// Created by Marco on 13/06/2025.
//

#include "pic.h"
#include "../../io/io.h"
#include "../../time/time.h"

#define PIC1            0x20                // Primary PIC
#define PIC2            0xA0                // Secondary PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)
#define PIC_EOI         0x20

void pic_remap() {
    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, 0x20); // IRQ0-7 a int 32-39
    outb(PIC2_DATA, 0x28); // IRQ8-15 a int 40-47
    outb(PIC1_DATA, 0x04);
    outb(PIC2_DATA, 0x02);
    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0x0);
    outb(PIC2_DATA, 0x0);
}

void pic_send_eoi(unsigned char irq)
{
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}