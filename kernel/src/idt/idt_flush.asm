[bits 32]
global idt_flush

idt_flush:
    mov eax, [esp + 4]  ; Load the address of the IDT pointer from the stack
    lidt [eax]
    ret