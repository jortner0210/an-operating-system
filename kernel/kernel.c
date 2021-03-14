#include "low_level.h"

// Drivers
#include "../drivers/vga_buffer.h"

// TO DO: 
//  - Change the name of low_level 
//  - Change makefile so all binaries are sent to bin

void main() {
    
    vga_set_cursor_location(0, 0);
    vga_clear_screen();
}

