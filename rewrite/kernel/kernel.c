#include <oslib.h>
#include <vga_screen.h>


void kmain(void)
{
	vga_clear_screen(VGA_RESET_CURSOR);

	vga_print_string("EVEN\n another line test", VGA_BG_BLACK | VGA_FG_WHITE);
}