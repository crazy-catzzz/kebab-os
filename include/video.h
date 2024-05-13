#pragma once

#define COLOR_SCHEME_GREENMONO (char)0x2A
#define COLOR_SCHEME_BLACKGREY (char)0x07

void prints(char* str);
void printc(char c);
void printi(int i);
void clear();
void move_cursor(int x, int y);

void video_init_color(char color);
