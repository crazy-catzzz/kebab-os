#include "../include/idt.h"
#include "../include/kb.h"

struct IDT_Entry IDT[IDT_SIZE];

void keyboard_handler();

void fill_entry(int code, unsigned long handler) {
    unsigned long address;

    address = handler;
    IDT[code].offset_lowerbits = address & 0xFFFF;
    IDT[code].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[code].zero = 0;
    IDT[code].type_attribute = INTERRUPT_GATE;
    IDT[code].offset_higherbits = (address & 0xFFFF0000) >> 16;
}

void idt_init(void) {
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    // Aggiungo interrupt per tastiera
    fill_entry(0x21, (unsigned long)keyboard_handler);

    /*
    PIC1
    Command 0x20
    Data    0x21

    PIC2
    Command 0xA0
    Data    0xA1
    */

    // ICW1 Init
    write_port(PIC1_COMMAND, 0x11);
    write_port(PIC2_COMMAND, 0x11);

    // ICW2 vector offset
    write_port(PIC1_DATA, 0x20);
    write_port(PIC2_DATA, 0x28);

    // ICW3 Cascading (OFF)
    write_port(PIC1_DATA, 0x00);
    write_port(PIC2_DATA, 0x00);

    // ICW4 environment
    write_port(PIC1_DATA, 0x01);
    write_port(PIC2_DATA, 0x01);

    // Mask all interrupts
    write_port(PIC1_DATA, 0xFF);
    write_port(PIC2_DATA, 0xFF);

    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDT_Entry) * IDT_SIZE) + ((idt_address & 0xFFFF) << 16);
    idt_ptr[1] = idt_address >> 16;

    load_idt(idt_ptr);
}