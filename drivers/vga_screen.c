#include "vga_screen.h"

#include "../kernel/x86asm.h"
#include "../kernel/utils.h"

/*---------------------- EXTERNAL API ----------------------------*/

void vga_get_cursor_position(int *row, int *col)
{
    int offset;
    outb(VGA_CTRL_REG, VGA_CURSOR_LOCATION_HIGH);
    offset = inb(VGA_DATA_REG) << 8;    
    outb(VGA_CTRL_REG, VGA_CURSOR_LOCATION_LOW);
    offset += inb(VGA_DATA_REG);

    (*row) = offset / VGA_MAX_COLS;
    (*col) = offset % VGA_MAX_COLS;
}

int vga_set_cursor_position(int row, int col)
{
    if (row >= VGA_MAX_ROWS || col >= VGA_MAX_COLS) {
        return 0;
    }
    else {
        int arr_offset = (row * VGA_MAX_COLS) + col;
        outb(VGA_CTRL_REG, VGA_CURSOR_LOCATION_HIGH);
        outb(VGA_DATA_REG, (unsigned char)(arr_offset >> 8));

        outb(VGA_CTRL_REG, VGA_CURSOR_LOCATION_LOW);
        outb(VGA_DATA_REG, (unsigned char)arr_offset);
        return 1;
    }
}

//
// Sets the entire VGA memory buffer to 0
//
void vga_clear_screen()
{
    char *video_memory = (char *)VGA_VIDEO_MEMORY;
    for (int i = 0; i < VGA_MAX_ROWS; i++) {
        for (int j = 0; j < VGA_MAX_COLS; j++) {
            int idx = (i * VGA_MAX_COLS + j) * 2;
            video_memory[idx] = 0;
        }       
    }
    vga_set_cursor_position(0, 0);
}

void vga_print_string(char *string, unsigned char attribute)
{
    int idx = 0;
    int cur_row, cur_col;

    while (string[idx] != '\0') {
        vga_get_cursor_position(&cur_row, &cur_col);

        if (string[idx] != '\n') {
            vga_print_char(string[idx], cur_row, cur_col, attribute);
        }

        cur_col++;
                        
        if (string[idx] == '\n' || cur_col >= VGA_MAX_COLS) {
            cur_row++;
            int rc = vga_set_cursor_position(cur_row, 0);
            if (rc == 0) {
                vga_scroll_screen();
                vga_set_cursor_position(VGA_MAX_ROWS - 1, 0);

                vga_clear_row(VGA_MAX_ROWS - 1);
            }
        }
        else {
            vga_set_cursor_position(cur_row, cur_col);
        }

        idx++;
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
    return (row * VGA_MAX_COLS + col) * 2;
}

static void vga_scroll_screen()
{
    char *video_memory = (char *)VGA_VIDEO_MEMORY;
    for (int i = 1; i < VGA_MAX_ROWS; i++) {
        int prev_offset = vga_get_cell_offset(i - 1, 0);
        int curr_offset = vga_get_cell_offset(i, 0);
        memcopy(video_memory + prev_offset, video_memory + curr_offset, VGA_MAX_COLS * 2);
    }
}

static int vga_clear_row(int row)
{
    char *video_memory = (char *)VGA_VIDEO_MEMORY;
    for (int j = 0; j < VGA_MAX_COLS; j++) {
        int idx = (row * VGA_MAX_COLS + j) * 2;
        video_memory[idx] = 0;
    }       
}