#include <stdint.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

void dumpArray(const char *pBuf, size_t bufLen)
{
    int i;
    int isEol = 0;
    for (i = 0; i < bufLen; i++)
    {
        if (i % 16 == 0)
        {
            printf("%04x", i);
        }
        printf(" %02hhx", pBuf[i]);
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

int main(int argc, char *argv[])
{
    int subResult;
    time_t t;
    struct tm *pTm = NULL;
    size_t bufLen;
    char *pBuf = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s format [time] [bufLen]\n");
        return EXIT_FAILURE;
    }

    if (argc < 3)
    {
        t = time(NULL);
    }
    else
    {
        intmax_t v, v2;
        char *pEnd;
        v = strtoimax(argv[2], &pEnd, 10);
        if (*pEnd != '\0')
        {
            fprintf(stderr, "invalid time.\n");
            return EXIT_FAILURE;
        }
        t = (time_t) v;
        v2 = (intmax_t) t;
        if (v2 != v) {
            fprintf(stderr, "time overflow.\n");
            return EXIT_FAILURE;
        }
    }

    bufLen = (argc < 4) ? 256 : atoi(argv[3]);

    pBuf = malloc(bufLen + 1);
    if (!pBuf)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    pTm = localtime(&t);
    memset(pBuf, 'X', bufLen);
    pBuf[bufLen] = '\0';
    strftime(pBuf, bufLen, argv[1], localtime(&t));

    printf("%s\n", pBuf);

    dumpArray(pBuf, bufLen);

    return EXIT_SUCCESS;
}
