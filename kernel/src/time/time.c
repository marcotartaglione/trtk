//
// Created by Marco on 13/06/2025.
//

#include "time.h"

uint32_t tick_count = 0;

uint32_t uptime_us() {
    return tick_count * US_PER_TICK;
}

uint32_t uptime_ms() {
    return uptime_us() / 1000;
}
