#include "../include/mem.h"
#include <stddef.h>

// mem block (header)
typedef struct block {
    void* lower_bound;
    int size;
    struct block* next;
} block;

// mem pointer
void* mem = 0x200000;

block* top = NULL;

// aggiungo un blocco in fondo
block* create_block(int size) {
    void* ptr = mem;
    mem = mem + size + sizeof(block);

    block* ret = (block*)ptr;

    ret->lower_bound = ptr + sizeof(block);
    ret->size = size;
    ret->next = NULL;

    return ret;
}

void* kmalloc(int size) {
    block* first;
    block* prev = NULL;
    for (first = top; first != NULL; first = first->next) {
        if (first->size >= size) {
            if (prev != NULL) prev->next = first->next;
            return first->lower_bound;
        }
        prev = first;
    }
    
    // Se questo codice viene eseguito vuol dire che non ci sono blocchi abbastanza grandi
    block* b = create_block(size);
    return b->lower_bound;
}

void kfree(void* ptr) {
    block* b = ptr - sizeof(block);

    top->next = b;
    top = b;
}

// Copia la memoria da un puntatore gestito ad un altro
void kmemcpy(void* src, void* dest) {
    block* srcbptr = src - sizeof(block);
    block* destbptr = dest - sizeof(block);

    char* csrc = (char*)src;
    char* cdest = (char*)dest;

    if (srcbptr->size > destbptr->size) return;

    for (int i = 0; i < srcbptr->size / sizeof(char); i++) {
        cdest[i] = csrc[i];
    }
}