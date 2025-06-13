[BITS 32]

global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

extern irq_handler

%macro IRQ_STUB 1
irq%1:
    cli

    push dword 0              ; err_code = 0
    push dword %1 + 32        ; int_no (remapped IRQ number)

    pusha                     ; salva registri generali: eax, ecx, edx, ebx, esp, ebp, esi, edi (in ordine inverso)

    push ds
    push es
    push fs
    push gs

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov eax, esp              ; esp punta a gs, fs, es, ds, pusha regs, int_no, err_code
    push eax
    call irq_handler
    add esp, 4                ; pulisci argomento

    pop gs
    pop fs
    pop es
    pop ds

    popa                      ; ripristina registri generali

    add esp, 8                ; pop err_code + int_no

    sti
    iret
%endmacro

IRQ_STUB 0
IRQ_STUB 1
IRQ_STUB 2
IRQ_STUB 3
IRQ_STUB 4
IRQ_STUB 5
IRQ_STUB 6
IRQ_STUB 7
IRQ_STUB 8
IRQ_STUB 9
IRQ_STUB 10
IRQ_STUB 11
IRQ_STUB 12
IRQ_STUB 13
IRQ_STUB 14
IRQ_STUB 15

section .note.GNU-stack noalloc noexec nowrite
