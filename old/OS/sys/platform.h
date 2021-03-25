#ifndef PLATFORM_H
#define PLATFORM_H

#include <types.h>

uchar_t inb(unsigned short port);

void outb(unsigned short port, uchar_t data);

#endif