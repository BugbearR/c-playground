#include "cplayground/dump.h"

void cplayground_fdumpWithAddr(FILE *pFile, const void *pBuf, size_t bufLen)
{
    size_t i;
    const char *p = (const char *)pBuf;

    int isEol = 0;
    for (i = 0; i < bufLen; i++)
    {
        if (i % 16 == 0)
        {
            fprintf(pFile, "%04zx", i);
        }
        fprintf(pFile, " %02hhx", p[i]);
        if (i % 16 == 15)
        {
            fprintf(pFile, "\n");
            isEol = 1;
        }
        else
        {
            isEol = 0;
        }
    }
    if (!isEol)
    {
        fprintf(pFile, "\n");
    }
}
