bits 32

; Sono già in protected mode a 32 bit

; multiboot spec
section .text
    align 4
    dd 0x1BADB002
    dd 0x00
    dd - (0x1BADB002 + 0x00)

global start
extern kernel_main

start:
    cli ; clear interrupts
    mov esp, stack_space
    call kernel_main
    hlt

section .bss
resb 8192
stack_space: