//
// Created by Marco on 13/06/2025.
//

#ifndef TRTK_TIME_H
#define TRTK_TIME_H

#include <stdint.h>

#define PIT_BASE_FREQUENCY  1193182
#define TIMER_FREQUENCY     0xFFFF
#define PIT_DIVISOR         (PIT_BASE_FREQUENCY / TIMER_FREQUENCY)
#define US_PER_TICK         1000000 / PIT_DIVISOR
extern uint32_t tick_count;

uint32_t uptime_us();
uint32_t uptime_ms();

#endif //TRTK_TIME_H
