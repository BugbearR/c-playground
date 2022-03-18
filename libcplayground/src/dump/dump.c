#include <stdio.h>
#include <stdlib.h>

#include "cplayground/dump.h"

void cplayground_dump(const void *pBuf, size_t bufLen)
{
    cplayground_fdump(stdout, pBuf, bufLen);
}
