//
// Created by Marco on 13/06/2025.
//

#include "time.h"
#include "../io/io.h"

uint32_t pit_ticks = 0;
uint16_t pit_current_frequency = PIT_HZ;

void pit_set_frequency(uint16_t frequency) {
    if (frequency == 0) {
        frequency = PIT_HZ;
    }
    pit_current_frequency = frequency;
    uint16_t divisor = PIT_FREQUENCY / pit_current_frequency;

    outb(PIT_COMMAND, 0x36);                    // Command to set PIT mode and channel
                                                // 00110110b [7-6]=Channel [5-4]=Access mode [3-1]=Mode [0]=Binary
                                                // Channel 0, Access mode: lobyte/hibyte, Mode 3 (Square wave generator), Binary mode

    outb(PIT_CHANNEL0, divisor & 0xFF);         // Send low byte of divisor
    outb(PIT_CHANNEL0, (divisor >> 8) & 0xFF);  // Send high byte of divisor
}

uint32_t time_get_ms() {
    uint32_t ms = pit_ticks * (1000 / PIT_HZ);
    return ms;
}

void time_handler() {
    pit_ticks++;
}