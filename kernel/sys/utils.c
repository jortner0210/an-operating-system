#include "utils.h"

void memcopy(unsigned char *dest, unsigned char *src, int bytes)
{
    for (int i = 0; i < bytes; i++)
        dest[i] = src[i];
}

void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}