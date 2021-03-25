#include <oslib.h>

/*---------------------- MEMORY FUNCTIONS ----------------------------*/

//
// Copy bytes from one location to another.
//
void memcpy
(
    void *dest, 
    void *src,
    size_t bytes
)
{
    char *d = (char *)dest;
    char *s = (char *)src;
    for (int i = 0; i < bytes; i++)
        d[i] = s[i];
}

//
// Set a number of bytes to val.
//
void memset
(
    void *dest, 
    uchar_t val,
    size_t bytes
)
{
    uchar_t *d = (uchar_t *)dest;
    for (int i = 0; i < bytes; i++)
        d[i] = val;
}