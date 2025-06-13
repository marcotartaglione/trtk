//
// Created by Marco on 13/06/2025.
//

#include "pic.h"
#include "../../io/io.h"

#define PIC1            0x20                // Primary PIC
#define PIC2            0xA0                // Secondary PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1+1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2+1)
#define PIC_EOI         0x20

// Every pic can handle 8 IRQs. With the master and slave PICs, we can handle 16 IRQs in total.
// The slave PIC interrupts must be handled by the master PIC on one of its available space.

void pic_remap() {
    outb(PIC1_COMMAND, 0x11);       // Start initialization sequence for master PIC (Initialization Command Word 1)
                                             // 00010001b bit 4 -> Initialization sequence required
                                             // 00010001b bit 1 -> ICW4 (4 command words) required
    outb(PIC1_DATA, 0x20);          // Interrupt vector offset for master PIC: IRQ0-7 -> 0x20-0x27
    outb(PIC1_DATA, 0x04);          // Slave connected to IRQ2 (100b -> bit 2 = channel 2)
    outb(PIC1_DATA, 0x01);          // 00000001b bit 0 -> x86 protected mode
    outb(PIC1_DATA, 0x0);           // All interrupts are enabled

    outb(PIC2_COMMAND, 0x11);       // Start initialization sequence for slave PIC
    outb(PIC2_DATA, 0x28);
    outb(PIC2_DATA, 0x02);          // Master PIC is connected to IRQ2 (10b -> bit 2 = channel 2)
    outb(PIC2_DATA, 0x01);
    outb(PIC2_DATA, 0x0);
}

void pic_send_eoi(unsigned char irq)
{
    if (irq >= 8)
        outb(PIC2_COMMAND, PIC_EOI);

    outb(PIC1_COMMAND, PIC_EOI);
}