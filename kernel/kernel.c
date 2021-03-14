#include "x86asm.h"

// Drivers
#include "../drivers/vga_buffer.h"


void main() {
    vga_set_cursor_location(0, 0);
    vga_clear_screen();

    vga_print_char('C', 0, 0, VGA_FG_BLUE | VGA_BG_GRAY);
}

