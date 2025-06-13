global start
extern kernel_main

section .multiboot
align 4
    dd 0x1BADB002
    dd 0x00
    dd -(0x1BADB002 + 0x00)

section .text
start:
    cli
    mov esp, stack_top
    push ebx
    push eax
    call kernel_main
    cli
hang:
    hlt
    jmp hang

section .bss
resb 8192
stack_top:
