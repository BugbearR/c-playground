#include "cplayground/dump.h"

void cplayground_fdump(FILE *pFile, const void *pBuf, size_t bufLen)
{
    size_t remain;
    const char *p = (const char *)pBuf;
    fprintf(pFile, "%02hhx", *p++);
    for (remain = bufLen - 1; remain > 0; --remain)
    {
        fprintf(pFile, " %02hhx", *p++);
    }
}
