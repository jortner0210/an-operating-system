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

#define VGA_BUFFER_HEIGHT 25
#define VGA_BUFFER_WIDTH  80

// Default color scheme
#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define VGA_ADDRESS_REG 0x3d4
#define VGA_DATA_REG    0x3d5

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

#define VGA_FG_BLACK ((unsigned char)vga_black)
#define VGA_FG_BLUE ((unsigned char)vga_blue)

#define VGA_FG_WHITE ((unsigned char)vga_white)

#define VGA_BG_BLACK ((unsigned char)vga_black << 4)
#define VGA_BG_GREEN ((unsigned char)vga_green << 4)

#define VGA_BG_GRAY ((unsigned char)vga_gray << 4)

/*---------------------- EXTERNAL API ----------------------------*/

int vga_set_cursor_location(int row, int col);

void vga_clear_screen();

/*---------------------- INTERNAL API ----------------------------*/

int vga_print_char(unsigned char c, int row, int col, unsigned char attribute);


static int vga_get_cell_offset(int row, int col);