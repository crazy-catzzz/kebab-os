#include "../include/kb.h"
#include "../include/ioport.h"
#include "../include/mem.h"
#include <stddef.h>

char* kb_buffer;
int kb_index = 0;

void init_kb(void) {
    write_port(0x21, 0xFD); // 0xFD = 0b11111101

    // init buffer
    kb_buffer = (char*)kmalloc(sizeof(char) * 64);
}

// inserisco carattere nel buffer
void in_put_char(char c) {
    kb_buffer[kb_index] = c;
    kb_index++;
}

// Non ritorno direttamente il buffer per evitare che l'utente provi a liberare la sua memoria
// Copio i contenuti del buffer in un puntatore
void get_in_buffer(char* ptr) {
    kmemcpy(kb_buffer, ptr);
    flush_buffer();
}
void flush_buffer() {
    for (int i = 0; i < 64; i++) {
        kb_buffer[i] = '\0';
    }
    kb_index = 0;
}