//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_TIME_H
#define TRTK_TIME_H

#include <stdint.h>

#define PIT_CHANNEL0    0x40
#define PIT_COMMAND     0x43
#define PIT_FREQUENCY   1193182 // Frequency of the PIT in Hz

#define PIT_HZ          1000 // Desired frequency in Hz (1 kHz)

void pit_set_frequency(uint16_t frequency);
uint32_t time_get_ms();
void time_handler();

#endif //TRTK_TIME_H
