#include <isr.h>
#include <vga_screen.h>
#include <platform.h>

//
// INTERRUPTS:
//
// 0 - Division by zero exception
// 1 - Debug exception
// 2 - Non maskable interrupt
// 3 - Breakpoint exception
// 4 - 'Into detected overflow'
// 5 - Out of bounds exception
// 6 - Invalid opcode exception
// 7 - No coprocessor exception
// 8 - Double fault (pushes an error code)
// 9 - Coprocessor segment overrun
// 10 - Bad TSS (pushes an error code)
// 11 - Segment not present (pushes an error code)
// 12 - Stack fault (pushes an error code)
// 13 - General protection fault (pushes an error code)
// 14 - Page fault (pushes an error code)
// 15 - Unknown interrupt exception
// 16 - Coprocessor fault
// 17 - Alignment check exception
// 18 - Machine check exception
// 19-31 - Reserved
//


//
// Called from Assemby interrupt handler stub.
//
void isr_handler
(
    registers_t regs
)
{
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }

    uchar_t disp_attr = VGA_FG_YELLOW | VGA_BG_BLACK;
    vga_print_string("Interrupt Received, Int No: ", VGA_FG_LIGHT_RED | VGA_BG_BLACK);
    switch (regs.int_no)
    {
        case 0x0:
            vga_print_string("0 - Division By Zero.", disp_attr);
            break;

        case 0x1:
            vga_print_string("1 - Debug Exception.", disp_attr);
            break;

        case 0x2:
            vga_print_string("2 - Non Maskable Interrupt.", disp_attr);
            break;

        case 0x3:
            vga_print_string("3 - Breakpoint Exception.", disp_attr);
            break;
        
        case 0x4:
            vga_print_string("4 - Into Detected Overflow.", disp_attr);
            break;

        default:
            vga_print_string("-1 - Unregistered Interrupt.", VGA_FG_RED | VGA_BG_BLACK);
            break;
    }
    vga_print_string("\n", VGA_BG_BLACK | VGA_FG_WHITE);
}


void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
} 

void irq_handler
(
    registers_t regs
)
{
    vga_print_string("IRQ HANDLER\n", VGA_FG_RED | VGA_BG_BLUE);
    // Send an EOI (end of interrupt) signal to the PICs.
    // If this interrupt involved the slave.
    if (regs.int_no >= 40)
    {
        // Send reset signal to slave.
        outb(0xA0, 0x20);
    }
    // Send reset signal to master. (As well as slave, if necessary).
    outb(0x20, 0x20);

    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}