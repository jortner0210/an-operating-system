#include "x86asm.h"

// Drivers
#include "../drivers/vga_screen.h"

void main() {

    
    vga_clear_screen();
    
    vga_print_string("Different people look at I/O hardware in different ways. Electrical engineers look at it in terms ofchips, wires, power supplies, motors, and all the other physical components that make up thehardware. Programmers look at the interface presented to the softwarethe commands thehardware accepts, the functions it carries out, and the errors that can be reported back. In thisbook we are concerned with programming I/O devices, not designing, building, or maintainingthem, so our interest will be restricted to h\n", WHITE_ON_BLACK);

    for (int i = 0; i < 17; i++) {
        if (i % 2) 
            vga_print_string("EVEN PRINT\n", WHITE_ON_BLACK);
        else
            vga_print_string("odd print\n", WHITE_ON_BLACK);
    }
 
}

