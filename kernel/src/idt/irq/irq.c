//
// Created by Marco on 13/06/2025.
//

#include "irq.h"
#include "../idt.h"
#include "pic.h"
#include "../../console/console.h"
#include "../../time/time.h"

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_install() {
    pic_remap();                  // PIC1: IRQ0->32, PIC2: IRQ8->40

    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);
    idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
}

void irq_handler(struct regs *r) {
    uint32_t irq_number = r->int_no - 32;

    if (irq_number < 16) {
        switch (irq_number) {
            case 0:
                tick_count++;
                break;
            case 1:
                printf("IRQ1: Keyboard interrupt\n");
                break;
            case 2:
                printf("IRQ2: Cascade interrupt\n");
                break;
            case 3:
                printf("IRQ3: COM2 interrupt\n");
                break;
            case 4:
                printf("IRQ4: COM1 interrupt\n");
                break;
            case 5:
                printf("IRQ5: LPT2 interrupt\n");
                break;
            case 6:
                printf("IRQ6: Floppy disk interrupt\n");
                break;
            case 7:
                printf("IRQ7: LPT1 interrupt\n");
                break;
            case 8:
                printf("IRQ8: Real-time clock interrupt\n");
                break;
            case 9:
                printf("IRQ9: Redirected IRQ2 (usually unused)\n");
                break;
            case 10:
                printf("IRQ10: Unused or custom device\n");
                break;
            case 11:
                printf("IRQ11: Unused or custom device\n");
                break;
            case 12:
                printf("IRQ12: PS/2 Mouse interrupt\n");
                break;
            case 13:
                printf("IRQ13: FPU or math coprocessor interrupt\n");
                break;
            case 14:
                printf("IRQ14: Primary IDE hard drive interrupt\n");
                break;
            case 15:
                printf("IRQ15: Secondary IDE hard drive interrupt\n");
                break;
        }
    }
    pic_send_eoi(irq_number);
}