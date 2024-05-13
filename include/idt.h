#pragma once

#define IDT_SIZE 256
#define KERNEL_CODE_SEGMENT_OFFSET 0x08
#define INTERRUPT_GATE 0x8E

// PIC 1 & 2
#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

struct IDT_Entry { // Riga Interrupt Descriptor Table
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attribute;
    unsigned short int offset_higherbits;
};

void load_idt(unsigned long* idt_ptr); // ASM function
void idt_init(void);