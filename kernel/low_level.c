
#include "low_level.h"

//
// Receives an 8-bit value from an I/O location 
//
unsigned char inb(unsigned short port)
{
    // Assembly:
    // mov dx, port
    // in al, dx
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

//
// Sends an 8-bit value to an I/O location
//
inline void outb(unsigned short port, unsigned char val)
{
    // Assembly:
    // mov dx, port
    // out dx, al
    __asm__("out %%al, %%dx": : "a" (val), "d" (port));
}

unsigned short port_word_in(unsigned  short  port) 
{
    unsigned short result;
    __asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
    return  result;
}

void port_word_out(unsigned  short  port , unsigned  short  data) 
{
    __asm__("out %%ax, %%dx" : :"a" (data), "d" (port ));
}