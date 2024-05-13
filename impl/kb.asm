bits 32

global keyboard_handler
extern kb_main

keyboard_handler:
    call kb_main
    iretd