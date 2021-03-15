#ifndef OS_VGA_SCREEN_H
#define OS_VGA_SCREEN_H

//
// VGA text buffer is a 2D array with 25 rows and 80 columns
// which is directly written to the screen.
//
// VGA Starting address: 0xb8000
//
// Array entries:
//  - bits 0-7  : ASCII code
//  - bits 8-11 : Foreground color
//  - bits 12-14: Background color
//  - bit 15    : Blink
//
// Note: Cursor location is set by the number of chars into array.
//

#define VGA_VIDEO_MEMORY 0xb8000

#define VGA_MAX_ROWS 25
#define VGA_MAX_COLS 80

// Default color scheme
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define VGA_CTRL_REG 0x3d4
#define VGA_DATA_REG 0x3d5

// VGA Registers
#define VGA_CURSOR_LOCATION_HIGH 0x0e
#define VGA_CURSOR_LOCATION_LOW  0x0f

// Text Colors
enum vga_colors
{
    vga_black        = 0x00,
    vga_blue         = 0x01,
    vga_green        = 0x02,
    vga_cyan         = 0x03,
    vga_red          = 0x04,
    vga_purple       = 0x05,
    vga_brown        = 0x06,
    vga_gray         = 0x07,
    vga_dark_gray    = 0x08,
    vga_light_blue   = 0x09,
    vga_light_green  = 0x0a,
    vga_light_cyan   = 0x0b,    
    vga_light_red    = 0x0c,
    vga_light_purple = 0x0d,
    vga_yellow       = 0x0e,
    vga_white        = 0x0f
};

// Text Attributes
#define VGA_CHAR_BLINK ((unsigned char)0x01 << 7) //0x80

#define VGA_FG_BLACK        ((unsigned char)vga_black)
#define VGA_FG_BLUE         ((unsigned char)vga_blue)
#define VGA_FG_GREEN        ((unsigned char)vga_green)
#define VGA_FG_CYAN         ((unsigned char)vga_cyan)
#define VGA_FG_RED          ((unsigned char)vga_red)
#define VGA_FG_PURPLE       ((unsigned char)vga_purple)
#define VGA_FG_BROWN        ((unsigned char)vga_brown)
#define VGA_FG_GRAY         ((unsigned char)vga_gray)
#define VGA_FG_DARK_GRAY    ((unsigned char)vga_dark_gray)
#define VGA_FG_LIGHT_BLUE   ((unsigned char)vga_light_blue)
#define VGA_FG_LIGHT_GREEN  ((unsigned char)vga_light_green)
#define VGA_FG_LIGHT_CYAN   ((unsigned char)vga_light_cyan)
#define VGA_FG_LIGHT_RED    ((unsigned char)vga_light_red)
#define VGA_FG_LIGHT_PURPLE ((unsigned char)vga_light_purple)
#define VGA_FG_YELLOW       ((unsigned char)vga_yellow)
#define VGA_FG_WHITE        ((unsigned char)vga_white)

#define VGA_BG_BLACK  ((unsigned char)vga_black << 4)
#define VGA_BG_GREEN  ((unsigned char)vga_green << 4)
#define VGA_BG_CYAN   ((unsigned char)vga_cyan << 4)
#define VGA_BG_RED    ((unsigned char)vga_red << 4)
#define VGA_BG_PURPLE ((unsigned char)vga_purple << 4)
#define VGA_BG_BROWN  ((unsigned char)vga_brown << 4)
#define VGA_BG_GRAY   ((unsigned char)vga_gray << 4)

/*---------------------- EXTERNAL API ----------------------------*/

void vga_get_cursor_position(int *row, int *col);

int vga_set_cursor_position(int row, int col);

void vga_clear_screen();

void vga_print_string(char *string, unsigned char attribute);

/*---------------------- INTERNAL API ----------------------------*/

static int vga_print_char(unsigned char c, int row, int col, unsigned char attribute);

static int vga_get_cell_offset(int row, int col);

static void vga_scroll_screen();

static int vga_clear_row(int row);

#endif