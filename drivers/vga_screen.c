#include "vga_screen.h"

#include "../kernel/x86asm.h"

/*---------------------- EXTERNAL API ----------------------------*/

//
// Sets the screen cursor to a location.
//
// Returns 1: if location is within bounds of screen
// Returns 0: if location is outside the bounds of the screen
//
int vga_set_cursor_location(int row, int col)
{
    if ((row * col) >= (VGA_BUFFER_HEIGHT * VGA_BUFFER_WIDTH))
        return 0;
    else {
        int offset = vga_get_cell_offset(row, col) / 2;
        outb(VGA_ADDRESS_REG, VGA_CURSOR_LOCATION_HIGH);
        outb(VGA_DATA_REG, (unsigned char)(offset >> 8));

        outb(VGA_ADDRESS_REG, VGA_CURSOR_LOCATION_LOW);
        outb(VGA_DATA_REG, (unsigned char)offset);
    }   
}

//
// Sets the entire VGA memory buffer to 0
//
void vga_clear_screen()
{
    char *video_memory = (char *)VGA_VIDEO_MEMORY;
    for (int i = 0; i < VGA_BUFFER_HEIGHT; i++) {
        for (int j = 0; j < VGA_BUFFER_WIDTH; j++) {
            int idx = (i * VGA_BUFFER_WIDTH + j) * 2;
            video_memory[idx] = 0;
        }       
    }
}

/*---------------------- INTERNAL API ----------------------------*/

int vga_print_char(unsigned char c, int row, int col, unsigned char attibute)
{
    int offset = vga_get_cell_offset(row, col);
    unsigned char *video_memory = (char *)VGA_VIDEO_MEMORY;
    video_memory[offset] = c;
    video_memory[offset+1] = attibute;
}

//
// Map row and col coordinates to the memory offset of
// a particular display character cell from start of 
// video memory.
//
static int vga_get_cell_offset(int row, int col)
{
    return (row * VGA_BUFFER_WIDTH + col) * 2;
}