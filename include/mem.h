#pragma once

void* kmalloc(int size);
void kfree(void* ptr);
void kmemcpy(void* src, void* dest);