//
// VGA Driver
//
// SOURCES:
//  - http://www.osdever.net/FreeVGA/home.htm#vga
//

#ifndef VGA_SCREEN_H
#define VGA_SCREEN_H

#include <types.h>

#define VGA_VM_PTR (uchar_t *)0xb8000

// Screen device I/O ports
#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5

// VGA Registers
#define VGA_CURSOR_HIGH_REGISTER 0x0e
#define VGA_CURSOR_LOW_REGISTER  0x0f

#define VGA_COLUMNS 80
#define VGA_ROWS    25

// Default color scheme
#define WHITE_ON_BLACK 0x0f

// Text Attributes
#define VGA_CHAR_BLINK ((uchar_t)0x01 << 7) //0x80

//
// VGA Text Foreground and Background colors
//

#define VGA_FG_BLACK        ((uchar_t)0x00)
#define VGA_FG_BLUE         ((uchar_t)0x01)
#define VGA_FG_GREEN        ((uchar_t)0x02)
#define VGA_FG_CYAN         ((uchar_t)0x03)
#define VGA_FG_RED          ((uchar_t)0x04)
#define VGA_FG_PURPLE       ((uchar_t)0x05)
#define VGA_FG_BROWN        ((uchar_t)0x06)
#define VGA_FG_GRAY         ((uchar_t)0x07)
#define VGA_FG_DARK_GRAY    ((uchar_t)0x08)
#define VGA_FG_LIGHT_BLUE   ((uchar_t)0x09)
#define VGA_FG_LIGHT_GREEN  ((uchar_t)0x0a)
#define VGA_FG_LIGHT_CYAN   ((uchar_t)0x0b)
#define VGA_FG_LIGHT_RED    ((uchar_t)0x0c)
#define VGA_FG_LIGHT_PURPLE ((uchar_t)0x0d)
#define VGA_FG_YELLOW       ((uchar_t)0x0e)
#define VGA_FG_WHITE        ((uchar_t)0x0f)

#define VGA_BG_BLACK  ((uchar_t)0x00 << 4)
#define VGA_BG_BLUE   ((uchar_t)0x01 << 4)
#define VGA_BG_GREEN  ((uchar_t)0x02 << 4)
#define VGA_BG_CYAN   ((uchar_t)0x03 << 4)
#define VGA_BG_RED    ((uchar_t)0x04 << 4)
#define VGA_BG_PURPLE ((uchar_t)0x05 << 4)
#define VGA_BG_BROWN  ((uchar_t)0x06 << 4)

/*---------------------- EXTERNAL API ----------------------------*/

uint8_t vga_put_cursor
(
    uint8_t r, 
    uint8_t c
);

void vga_get_cusor
(
    uint8_t *r, 
    uint8_t *c
);

uint8_t vga_put_char
(
    uint8_t r, 
    uint8_t c, 
    char character,
    uchar_t attr
);

enum VGA_CS_CUR_OPT
{
    VGA_CLEAR_CURSOR,
    VGA_KEEP_CURSOR,
    VGA_RESET_CURSOR
};

void vga_clear_screen
(
    enum VGA_CS_CUR_OPT cursor
);

uint8_t vga_print_string
(
    char *string,
    uchar_t attr
);

/*---------------------- INTERNAL API ----------------------------*/

static uint8_t vga_position_inbounds
(
    uint8_t r,
    uint8_t c
);

static void vga_scroll_screen();

static uint8_t vga_clear_row
(
    uint8_t r
);

#endif