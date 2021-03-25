#include <platform.h>

//
// Receives an 8-bit value from an I/O location 
//
uchar_t inb(unsigned short port)
{
    // Assembly:
    // mov dx, port
    // in al, dx
    uchar_t result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

//
// Sends an 8-bit value to an I/O location
//
inline void outb(unsigned short port, uchar_t val)
{
    // Assembly:
    // mov dx, port
    // out dx, al
    __asm__("out %%al, %%dx": : "a" (val), "d" (port));
}
