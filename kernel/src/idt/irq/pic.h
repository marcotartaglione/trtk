//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_PIC_H
#define TRTK_PIC_H

// Programmable Interrupt Controller (PIC) definitions and functions
// for remapping and sending End of Interrupt (EOI) signals.

void pic_remap();
void pic_send_eoi(unsigned char irq);

#endif //TRTK_PIC_H
