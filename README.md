# A simple Bootloader and x86 Kernel

# Install:
    - First install Bochs Emulator: http://bochs.sourceforge.net/getcurrent.html
    - Run commands:
        * mkdir bin
        * make all
        * make run
    - At the bochs terminal prompt type c for continue executing
    - Press enter

# Supported Drivers:

## VGA Screen:
    - int vga_set_cursor_location(int row, int col)
    - void vga_clear_screen()
