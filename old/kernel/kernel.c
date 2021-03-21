#include "sys/x86asm.h"
#include "sys/idt.h"

#include <stdint.h>

// Drivers
#include "../drivers/vga_screen.h"

char *test = "IN C KERNEL\n";

void main() {
    init_descriptor_table();

    vga_clear_screen();

    vga_print_string("test string\n", VGA_FG_CYAN | VGA_BG_GRAY);
    
    uint16_t x = 10;

    __asm volatile ("int $0x0");
    __asm volatile ("int $0x1"); 

    vga_print_string("another string\n", VGA_FG_CYAN | VGA_BG_GRAY);
}

