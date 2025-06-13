[bits 32]
global gdt_flush

gdt_flush:
    mov eax, [esp + 4]  ; Get the address of the GDT from the stack
    lgdt [eax]          ; Load the GDT

    mov ax, 0x10        ; Set the data segment selector
    mov ds, ax          ; Load the data segment
    mov es, ax          ; Load the extra segment
    mov fs, ax          ; Load the fs segment
    mov gs, ax          ; Load the gs segment
    mov ss, ax          ; Load the stack segment

    jmp 0x08:flush_code ; Jump to the code segment to flush the pipeline

flush_code:
    ret                 ; Return from the function, now the GDT is loaded