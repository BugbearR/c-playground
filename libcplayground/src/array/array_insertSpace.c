#include <cplayground/array.h>

#include <string.h>

void cplayground_array_insertSpace(void *pArray, size_t elmSize, size_t capacity, size_t elmCount, size_t index, size_t len)
{
    size_t moveLen = elmSize * ((elmCount + len <= capacity) ? (elmCount - index) : (capacity - (index + len)));
    char *pBase = pArray;
    char *pSrc = pBase + elmSize * index;
    char *pDst = pSrc + elmSize * len;
    memmove(pDst, pSrc, moveLen);
}
