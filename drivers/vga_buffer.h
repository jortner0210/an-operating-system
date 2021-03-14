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

enum vga_colors
{
    vga_black = 0x0,
    vga_blue  = 0x1,
    vga_green = 0x2
};


/*---------------------- EXTERNAL API ----------------------------*/

int vga_set_cursor_location(int row, int col);

void vga_clear_screen();

/*---------------------- INTERNAL API ----------------------------*/

static int vga_get_char_offset(int row, int col);

static int vga_get_cell_offset(int row, int col);