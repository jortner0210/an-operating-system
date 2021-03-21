#ifndef OS_UTILS_H
#define OS_UTILS_H

#include <stdint.h>

void memcopy(unsigned char *dest, unsigned char *src, int bytes);
void memset(uint8_t *dest, uint8_t val, uint32_t len);

#endif