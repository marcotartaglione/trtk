//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_IDT_H
#define TRTK_IDT_H

// Interrupt Descriptor Table
// The IDT is a data structure used in x86 architecture to define the entry points for interrupt handlers.

#include <stdint.h>

struct idt_entry {
    uint16_t base_low;      // Lower 16 bits of the handler function address
    uint16_t sel;           // Kernel segment selector
    uint8_t  always0;       // This must always be zero
    uint8_t  flags;         // Flags to specify the type of gate (interrupt, trap, etc.)
    uint16_t base_high;     // Upper 16 bits of the handler function address
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_install();

#endif //TRTK_IDT_H
