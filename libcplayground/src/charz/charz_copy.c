#include <cplayground/charz.h>

char *cplayground_charz_copy(char *pDst, size_t dstLen, const char *pSrc)
{
    if (dstLen == 0)
    {
        return pDst;
    }

    const char *pSrcWk = pSrc;
    char *pDstWk = pDst;
    char *pDstEnd = pDst + dstLen - 1;
    char c = 1;
    while (pDstWk < pDstEnd && (c = (*pDstWk++ = *pSrcWk++)))
        ;
    if (c)
    {
        *pDstWk = '\0';
    }
    return pDst;
}
