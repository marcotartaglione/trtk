//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_GDT_H
#define TRTK_GDT_H

// GLOBAL DESCRIPTOR TABLE
// The GDT is a data structure used in x86 architecture to define the characteristics of the various memory segments used in the system.
// It contains entries that describe the base address, limit, and access rights of each segment.

#include <stdint.h>

struct gdt_entry {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern void gdt_flush(uint32_t);

void gdt_install();

#endif //TRTK_GDT_H
