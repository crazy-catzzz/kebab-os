#include "../include/video.h"
#include "../include/string.h"
#include "../include/ioport.h"

volatile char* vmem = (volatile char*)0xB8000;

#define SCREEN_COLS 80
#define SCREEN_ROWS 25
#define CELL_SIZE 2

// SCREEN COORDS
int lineno = 0; // curr_row
int colno = 0;  // curr_col

// ACTUAL SCREEN INDEX
int buf_index = 0;

char* color;
void video_init_color(char vcolor) {
    color = vcolor;
}

void prints(char* str) {
    for (int j = 0; str[j] != 0; j++) {
        printc(str[j]);
    }
}

void printc(char c) {
    if (c != 0) {
        buf_index = colno + (SCREEN_COLS * lineno * CELL_SIZE);
        // Handle newline
        if (c == '\n') {
            lineno++;
            colno = 0;
            move_cursor(colno / 2, lineno);
            return;
        }
        // Handle backspace
        if (c == '\b') {     
            colno -= CELL_SIZE;

            // Don't delete line
            if (colno < 0) {
                colno = 0;
            }
            move_cursor(colno / 2, lineno);

            buf_index = colno + (SCREEN_COLS * lineno * CELL_SIZE);
            vmem[buf_index] = ' ';
            return;
        }

        vmem[buf_index] = c;
        vmem[buf_index + 1] = color;

        colno += CELL_SIZE;
        move_cursor(colno / 2, lineno);
    }
}

void printi(int i) {
    // Convert int to string
    int n = i;
    int j = 0;
    char* ptr;
    do {
        char* base_ten_map = "0123456789";
        ptr[j] = base_ten_map[abs(i % 10)];
        i /= 10;
        j++;
    } while (i);
    int end = j - 1;
    int start = 0;
    
    while (start < end) {
        char temp = ptr[start];
        ptr[start] = ptr[end];
        ptr[end] = temp;
        start++;
        end--;
    }
    ptr[j] = '\0';

    // Print converted
    if (n < 0) {
        printc('-');
    }
    for(int k = 0; k < strlen(ptr); k++) {
        printc(ptr[k]);
    }
}

void clear_line(int line) {
    buf_index = (SCREEN_COLS * line * CELL_SIZE);

    while (buf_index < (SCREEN_COLS * 2) * line * CELL_SIZE) {
        vmem[buf_index] = ' ';
        vmem[buf_index + 1] = color;

        buf_index += CELL_SIZE;
    }
}

void clear(void) {
    int i = 0;
    while (i < SCREEN_COLS * SCREEN_ROWS * CELL_SIZE) {
        vmem[i] = ' ';

        vmem[i + 1] = color;

        i += CELL_SIZE;
    }
    lineno = 0;
}

// Cursor
void move_cursor(int x, int y) {
    unsigned short pos = x + (y * SCREEN_COLS);
    
    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char) (pos & 0xFF));
    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char) ((pos >> 8) & 0xFF));
}
