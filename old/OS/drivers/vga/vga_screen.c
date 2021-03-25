#include <vga_screen.h>
#include <oslib.h>
#include <platform.h>

//
// http://www.osdever.net/FreeVGA/vga/crtcreg.htm
//

/*---------------------- EXTERNAL API ----------------------------*/

//
// Places the cursor at a position (row, col).
//
// Because the cursor display is described by the attribute
// of the character where it is positioned, when cursor is
// placed, the character attribute will change as a consequence.
//
// Returns 0 fail, 1 success.
//
uint8_t vga_put_cursor
(
    uint8_t r, 
    uint8_t c
)
{
    uint8_t rc = vga_position_inbounds(r, c);

    if (rc) {
        uint16_t idx = TWO_TO_ONE(r, c, VGA_COLUMNS);
        outb(VGA_CTRL_REGISTER, VGA_CURSOR_HIGH_REGISTER);
        outb(VGA_DATA_REGISTER, (uchar_t)(idx >> 8));
        outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOW_REGISTER);
        outb(VGA_DATA_REGISTER, (uchar_t)(idx));

        // Set character attribute so that cursor displays white
        uchar_t *vm = VGA_VM_PTR;
        vm[(idx * 2) + 1] = VGA_FG_WHITE;
        return 1;
    }
    else
        return 0;
}

//
// Retreive the cursor position (row, col).
//
void vga_get_cusor
(
    uint8_t *r, 
    uint8_t *c
)
{
    uint16_t idx;
    outb(VGA_CTRL_REGISTER, VGA_CURSOR_HIGH_REGISTER);
    idx = ((uint16_t)inb(VGA_DATA_REGISTER)) << 8;
    outb(VGA_CTRL_REGISTER, VGA_CURSOR_LOW_REGISTER);
    idx += (uint16_t)inb(VGA_DATA_REGISTER);
    (*r) = ONE_TO_ROW(idx, VGA_COLUMNS);
    (*c) = ONE_TO_COL(idx, VGA_COLUMNS);
}

//
// Places a character at a position (row, col).
//
// Returns 0 fail, 1 successful.
//
uint8_t vga_put_char
(
    uint8_t r, 
    uint8_t c, 
    char character,
    uchar_t attr
)
{
    uchar_t *vm = VGA_VM_PTR;
    uint8_t rc = vga_position_inbounds(r, c);

    if (rc) {
        // Multiply index by two since character and attribute 
        // memory panels are interleaved.
        // i.e. index 0: character to display
        //      index 1: attribute of character
        uint16_t idx = TWO_TO_ONE(r, c, VGA_COLUMNS) * 2;
        vm[idx] = character;
        vm[idx+1] = attr;
        return 1;
    }
    else
        return 0;
}

//
// Clears the screen and sets all character attributes to 0.
// Side effect is that the cursor will not be visible.
//
void vga_clear_screen
(
    enum VGA_CS_CUR_OPT cursor
)
{
    uchar_t *vm = VGA_VM_PTR;
    
    // Clear video memory
    for (int i = 0; i < VGA_ROWS * 2; i++) {
		for (int j = 0; j < VGA_COLUMNS * 2; j++) {
			uint16_t idx = TWO_TO_ONE(i, j, VGA_COLUMNS);
			vm[idx] = 0;
		}
	}   

    switch (cursor)
    {
        case VGA_KEEP_CURSOR: ;
            uint8_t cursor_r, cursor_c;
            vga_get_cusor(&cursor_r, &cursor_c);
            vga_put_cursor(cursor_r, cursor_c);
            break;
        
        case VGA_RESET_CURSOR:
            vga_put_cursor(0, 0);
            break;
    }
}

//
//  Print a null terminate string to the terminal using the cursor position.
//  The screen will scroll when writing past the last line.  
//  Newline character: "\n"
//
uint8_t vga_print_string
(
    char *string,
    uchar_t attr
)
{
    uint16_t char_idx = 0;
    uint8_t row, col;
    uint8_t cursor_rc;

    while (string[char_idx] != NULL_TERMINATE) {
        vga_get_cusor(&row, &col);

        // Check for new line
        if (string[char_idx] == NEW_LINE) {
            row++;
            col = 0;
        }
        else {
            // Copy character to video memory
            vga_put_char(row, col, string[char_idx], attr);
            col++;
            
            if (col == VGA_COLUMNS) {
                row++;
                col = 0;
            }
        }

        // Increment cursor and scroll if max row reached
        cursor_rc = vga_put_cursor(row, col);
        if (!cursor_rc) {
            vga_scroll_screen();
            vga_clear_row(VGA_ROWS - 1);
        }

        char_idx++;
    }
}

/*---------------------- INTERNAL API ----------------------------*/

//
// Checks that a character position (row, col) is within the 
// bounds of video memory.
//
// Returns 0 if position is out of bounds and 1 if in bounds.
//
static uint8_t vga_position_inbounds
(
    uint8_t r,
    uint8_t c
)
{
    uint16_t idx = TWO_TO_ONE(r, c, VGA_COLUMNS);
    if (idx < (VGA_ROWS * VGA_COLUMNS) && r < VGA_ROWS && c < VGA_COLUMNS)
        return 1;
    else
        return 0;
}

//
// Move each line up by one. Clears the last line.
//
static void vga_scroll_screen()
{
    uchar_t *vm = VGA_VM_PTR;
    uint8_t cursor_r, cursor_c;

    vga_get_cusor(&cursor_r, &cursor_c);

    // Copy each row to the row before.
    for (int i = 1; i < VGA_ROWS; i++) {
        uint16_t dest_idx = TWO_TO_ONE((i-1), 0, VGA_COLUMNS) * 2;
        uint16_t src_idx = TWO_TO_ONE(i, 0, VGA_COLUMNS) * 2;
        memcpy(&vm[dest_idx], &vm[src_idx], VGA_COLUMNS * 2);
    }

    if (cursor_r != 0 && cursor_r != (VGA_ROWS - 1)) {
        cursor_r--;
    }
    cursor_c = 0;

    vga_put_cursor(cursor_r, cursor_c);
}

//
// Clear all character in a row.
// Returns 0 fail, 1 success
//
static uint8_t vga_clear_row
(
    uint8_t r
)
{
    uchar_t *vm = VGA_VM_PTR;
    uint8_t rc = vga_position_inbounds(r, 0);

    if (rc) {
        uint8_t cursor_r, cursor_c;
        uint16_t idx = TWO_TO_ONE(r, 0, VGA_COLUMNS) * 2;

        memset(&vm[idx], 0, VGA_COLUMNS * 2);

        // Reset cursor to its current postion. 
        // If cursor is located at cleared row it will also 
        // be cleared if it isn't reset.
        vga_get_cusor(&cursor_r, &cursor_c);
        vga_put_cursor(cursor_r, cursor_c);
    }
    else
        return 0;
}