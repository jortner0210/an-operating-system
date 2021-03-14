#include "x86asm.h"

// Drivers
#include "../drivers/vga_screen.h"

void main() {

    vga_set_cursor_location(0, 0);
    vga_clear_screen();

    vga_print_string("To print a character to the screen in VGA text mode, one has to write it to the text buffer of the VGA hardware. The VGA text buffer is a two-dimensional array with typically 25 rows and 80 columns, which is directly rendered to the screen. Each array entry describes a single screen character through the following format:\n", WHITE_ON_BLACK);
    
    //for (int i = 0; i < 21; i++) {
    //    if (i % 2 == 0) {
    //        vga_print_string("Another line test\n", WHITE_ON_BLACK);
    //    }
    //    else {
    //        vga_print_string("TESTING PRINT\n", WHITE_ON_BLACK);
    //    }
    //}
    
}

