#include <cplayground/array.h>

#include <string.h>

void cplayground_array_fill(void *pArray, size_t elmSize, size_t index, size_t len, void *pValue)
{
    char *pBase = pArray;
    char *pStart = pBase + elmSize * index;
    char *pEnd = pStart + elmSize * len;
    char *p;
    for (p = pStart; p < pEnd; p += elmSize)
    {
        memcpy(p, pValue, elmSize);
    }
}
