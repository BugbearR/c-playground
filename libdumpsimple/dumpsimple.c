#include <stdio.h>
#include <stdlib.h>

void dumpSimple(const void *pBuf, size_t bufLen)
{
    size_t i;
    const char *p = (const char *)pBuf;

    int isEol = 0;
    for (i = 0; i < bufLen; i++)
    {
        if (i % 16 == 0)
        {
            printf("%04x", i);
        }
        printf(" %02hhx", p[i]);
        if (i % 16 == 15)
        {
            printf("\n");
            isEol = 1;
        }
        else
        {
            isEol = 0;
        }
    }
    if (!isEol)
    {
        printf("\n");
    }
}
