#include <stdio.h>
#include <stdlib.h>

#include "cplayground/dump.h"

void cplayground_dumpWithAddr(const void *pBuf, size_t bufLen)
{
    cplayground_fdumpWithAddr(stdout, pBuf, bufLen);
}
