//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_IO_H
#define TRTK_IO_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);

#endif //TRTK_IO_H
