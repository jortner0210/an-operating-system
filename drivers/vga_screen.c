#include "vga_screen.h"

#include "../kernel/x86asm.h"
#include "../kernel/utils.h"

/*---------------------- EXTERNAL API ----------------------------*/

//
// Retreive the row and col location of the cursor
//
void vga_get_cursor_location(int *row, int *col)
{
    int offset;
    outb(VGA_ADDRESS_REG, VGA_CURSOR_LOCATION_HIGH);
    offset = inb(VGA_DATA_REG) << 8;
    outb(VGA_ADDRESS_REG, VGA_CURSOR_LOCATION_LOW);
    offset += inb(VGA_DATA_REG);

    // VGA hardware reports cursor location as character offset.
    // Multiply by two to get cell location. 
    (*row) = offset / VGA_BUFFER_WIDTH;
    (*col) = offset % VGA_BUFFER_WIDTH;
}

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
    vga_set_cursor_location(0, 0);
}

void vga_print_string(char *string, unsigned char attribute)
{
    int idx = 0;
    int cur_row, cur_col;

    while (string[idx] != '\0') {
        vga_get_cursor_location(&cur_row, &cur_col);

        if (string[idx] == '\n') {
            vga_set_cursor_location(cur_row + 1, 0);
        }
        else {
            vga_print_char(string[idx], cur_row, cur_col, attribute);
            if (cur_col + 1 == VGA_BUFFER_WIDTH) {
                vga_set_cursor_location(cur_row + 1, 0);
            }
            else {
                vga_set_cursor_location(cur_row, cur_col + 1);
            }
        }
                        
        idx++;
    }

    // Handle scrolling
    vga_get_cursor_location(&cur_row, &cur_col);
    if (cur_row == VGA_BUFFER_HEIGHT) {
        for (int r = 1; r < VGA_BUFFER_HEIGHT; r++) {
            //vga_clear_row(r);
            char *video_memory = (char *)VGA_VIDEO_MEMORY;

            memcopy(video_memory + vga_get_cell_offset(r-1, 0), 
                    video_memory + vga_get_cell_offset(r, 0), 
                    VGA_BUFFER_WIDTH * 2);
        }

        vga_clear_row(VGA_BUFFER_HEIGHT - 1);

        vga_set_cursor_location(24, 0);
    }
}

/*---------------------- INTERNAL API ----------------------------*/

static int vga_print_char(unsigned char c, int row, int col, unsigned char attibute)
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

static void scroll_screen()
{
    unsigned char *video_memory_copy;
}

int vga_clear_row(int row)
{
    char *video_memory = (char *)VGA_VIDEO_MEMORY;
    int offset = vga_get_cell_offset(row, 0);
    video_memory += offset;
    for (int i = 0; i < VGA_BUFFER_WIDTH * 2; i++)
        video_memory[i] = 0;
}