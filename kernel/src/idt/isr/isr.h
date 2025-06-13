//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_ISR_H
#define TRTK_ISR_H

#include <stdint.h>
#include "../idt.h"

struct regs
{
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed));

void isr_install();
void isr_handler(struct regs *r);

#endif //TRTK_ISR_H
