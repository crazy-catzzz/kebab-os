#include "include/video.h"
#include "include/idt.h"
#include "include/kb.h"
#include <stdbool.h>

void kernel_main() {
    video_init_color(COLOR_SCHEME_BLACKGREY);
    clear();

    idt_init();
    init_kb();
    
    prints("KebabOS v1.0-alpha-scarraFOSS\n");
    prints("Mi piacciono gli spaghetti\n");
    prints("Kotte sei un geek\n");

    char* keys = "
    
    while(true);
}
