#include <cplayground/array.h>

#include <string.h>

void cplayground_array_delete(void *p, size_t elmSize, size_t elmCount, size_t index, size_t len)
{
    size_t moveLen = elmSize * len;
    char *pBase = p;
    char *pDst = pBase + elmSize * index;
    char *pSrc = pDst + elmSize * len;
    memmove(pDst, pSrc, moveLen);
}
