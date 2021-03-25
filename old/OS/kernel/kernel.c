#include <oslib.h>
#include <descriptor_tables.h>
#include <vga_screen.h>

void test_vga_colors();
void test_interrupts();

void kmain(void)
{
	vga_clear_screen(VGA_RESET_CURSOR);
	init_descriptor_tables();

	asm volatile("int $0x3");
    asm volatile("int $0x4");

	//test_vga_colors();

	//test_interrupts();
	
}

void test_vga_colors()
{
	vga_print_string("VGA PRINT STRING FOREGROUND BLACK\n", VGA_FG_BLACK | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND BLUE\n", VGA_FG_BLUE | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND GREEN\n", VGA_FG_GREEN | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND CYAN\n", VGA_FG_CYAN | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND RED\n", VGA_FG_RED | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND PURPLE\n", VGA_FG_PURPLE | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND BROWN\n", VGA_FG_BROWN | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND GRAY\n", VGA_FG_GRAY | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND DARK_GRAY\n", VGA_FG_DARK_GRAY | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND LIGHT_BLUE\n", VGA_FG_LIGHT_BLUE | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND LIGHT_GREEN\n", VGA_FG_LIGHT_GREEN | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND LIGHT_CYAN\n", VGA_FG_LIGHT_CYAN | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND LIGHT_RED\n", VGA_FG_LIGHT_RED | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND LIGHT_PURPLE\n", VGA_FG_LIGHT_PURPLE | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND YELLOW\n", VGA_FG_YELLOW | VGA_BG_BLACK);
	vga_print_string("VGA PRINT STRING FOREGROUND WHITE\n", VGA_FG_WHITE | VGA_BG_BLACK);
	
	
	vga_print_string("VGA PRINT STRING BACKGROUND BLACK\n", VGA_BG_BLACK | VGA_FG_WHITE);
	vga_print_string("VGA PRINT STRING BACKGROUND BLUE\n", VGA_BG_BLUE | VGA_FG_WHITE);
	vga_print_string("VGA PRINT STRING BACKGROUND GREEN\n", VGA_BG_GREEN | VGA_FG_WHITE);
	vga_print_string("VGA PRINT STRING BACKGROUND CYAN\n", VGA_BG_CYAN | VGA_FG_WHITE);
	vga_print_string("VGA PRINT STRING BACKGROUND RED\n", VGA_BG_RED | VGA_FG_WHITE);
	vga_print_string("VGA PRINT STRING BACKGROUND PURPLE\n", VGA_BG_PURPLE | VGA_FG_WHITE);
	vga_print_string("VGA PRINT STRING BACKGROUND BROWN\n", VGA_BG_BROWN | VGA_FG_WHITE);

	vga_print_string("/----------------- VGA SCREEN TEST PASSED -----------------/\n", VGA_FG_GREEN | VGA_BG_BLACK);
}

void test_interrupts()
{
	vga_print_string("/----------------- TESTING INTERRUPTS... -----------------/\n\n", VGA_FG_GREEN | VGA_BG_BLACK);

	//asm volatile ("int $0x0");
	//asm volatile ("int $0x1");
	//asm volatile ("int $0x2");
	//asm volatile ("int $0x3");
	//asm volatile ("int $0x4");
	//asm volatile ("int $0x5");
	//asm volatile ("int $0x6");
	//asm volatile ("int $0x7");

	//asm volatile ("int $0x8");
	
	//asm volatile ("int $0x9");
	//asm volatile ("int $0xa");
	//asm volatile ("int $0xb");
	//asm volatile ("int $0xc");
	//asm volatile ("int $0xd");
	//asm volatile ("int $0xe");
	//asm volatile ("int $0xf");
	//asm volatile ("int $0x10");
	//asm volatile ("int $0x11");
	//asm volatile ("int $0x12");
	//asm volatile ("int $0x13");
	//asm volatile ("int $0x14");
	//asm volatile ("int $0x15");
	//asm volatile ("int $0x16");
	//asm volatile ("int $0x17");
	//asm volatile ("int $0x18");
	//asm volatile ("int $0x19");
	//asm volatile ("int $0x1a");
	//asm volatile ("int $0x1b");
	//asm volatile ("int $0x1c");
	//asm volatile ("int $0x1d");
	//asm volatile ("int $0x1e");

	vga_print_string("\n/----------------- INTERRUPT TEST PASSED -----------------/\n", VGA_FG_GREEN | VGA_BG_BLACK);
}