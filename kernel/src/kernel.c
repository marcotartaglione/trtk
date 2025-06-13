//
// Created by Marco on 13/06/2025.
//
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "idt/isr/isr.h"
#include "idt/irq/irq.h"
#include "console/console.h"
#include "time/time.h"

void kernel_main() {
    clear_screen();
    gdt_install();
    printf("GDT loadad successfully!\n");
    idt_install();
    printf("IDT loadad successfully!\n");
    isr_install();
    printf("ISR loadad successfully!\n");
    irq_install();
    printf("IRQ loadad successfully!\n");

    asm volatile("sti");

    while (1) {
        printf("Time: %lu s\r", uptime_ms() / 1000);
        move_cursor();
    }
}