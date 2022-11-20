#include <cplayground/array.h>

#include <string.h>

void cplayground_array_clear(void *pArray, size_t elmSize, size_t index, size_t len)
{
    char *pBase = pArray;
    char *pStart = pBase + elmSize * index;
    memset(pStart, 0, elmSize * len);
}
