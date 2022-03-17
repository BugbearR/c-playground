#include <stdio.h>
#include <stdlib.h>

#include "cplayground/dump.h"

void cplayground_dumpOut(const void *pBuf, size_t bufLen)
{
    size_t remain;
    const char *p = (const char *)pBuf;
    printf("%02hhx", *p++);
    for (remain = bufLen - 1; remain > 0; --remain)
    {
        printf(" %02hhx", *p++);
    }
}
