//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_IRQ_H
#define TRTK_IRQ_H

// Interrupt Request
// different from ISRs, IRQs are hardware interrupts

#include <stdint.h>
#include "../isr/isr.h"

void irq_install();
void irq_handler(struct regs *r);

#endif //TRTK_IRQ_H
