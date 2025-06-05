#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <unistd.h>

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
    int result = EXIT_FAILURE;
    int subResult;
    FILE *pFile = NULL;
    int bufLen;
    char *pBuf = NULL;
    char *pLine = NULL;

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s path buffer_length\n", argv[0]);
        return EXIT_FAILURE;
    }

    bufLen = atoi(argv[2]);

    pBuf = malloc(bufLen + 1); // +1 for end of string
    pBuf[bufLen] = '\0';

    pFile = fopen(argv[1], "rt");

    for (;;)
    {
        // fill by dummy data
        memset(pBuf, 'X', bufLen);
        errno = 0;
        pLine = fgets(pBuf, bufLen, pFile);
        int subErrno = errno;
        fprintf(stderr, "errno: %d\n", subErrno);
        if (!pLine)
        {
            if (feof(pFile))
            {
                break;
            }
            if (ferror(pFile))
            {
                fprintf(stderr, "fgets: stream error.\n");
            }
            fprintf(stderr, "fgets: %s\n", strerror(subErrno));
            goto EXIT_FUNC;
        }
        printf("----------\n");
        printf("\"%s\"\n", pLine);
        dumpArray(pBuf, bufLen);
    }

    result = EXIT_SUCCESS;

EXIT_FUNC:
    if (pBuf)
    {
        free(pBuf);
    }

    if (pFile)
    {
        fclose(pFile);
    }

    return result;
}
