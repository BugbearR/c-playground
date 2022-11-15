#include <cplayground/charz.h>

char *cplayground_charz_copyLimit(char *pDst, size_t dstLen, const char *pSrc, size_t srcLen)
{
    if (dstLen == 0)
    {
        return pDst;
    }

    const char *pSrcWk = pSrc;
    const char *pSrcEnd = pSrc + srcLen;
    char *pDstWk = pDst;
    char *pDstEnd = pDst + dstLen - 1;
    char c = 1;
    while (pDstWk < pDstEnd && pSrcWk < pSrcEnd && (c = (*pDstWk++ = *pSrcWk++)))
        ;
    if (c)
    {
        *pDstWk = '\0';
    }
    return pDst;
}
