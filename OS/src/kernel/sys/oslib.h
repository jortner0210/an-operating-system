#ifndef OS_LIB_H
#define OS_LIB_H

#include <types.h>

/*---------------------- INDEXING ----------------------------*/

#define TWO_TO_ONE(i, j, width) ((i * width) + j)
#define ONE_TO_ROW(idx, width) (idx / width)
#define ONE_TO_COL(idx, width) (idx % width)

/*---------------------- MEMORY FUNCTIONS ----------------------------*/

void memcpy
(
    void *dest, 
    void *src,
    size_t bytes
);

void memset
(
    void *dest, 
    uchar_t val,
    size_t bytes
);

/*---------------------- STRING FUNCTIONS ----------------------------*/

#endif