#include <stdio.h>
#include <stdlib.h>
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
    char buf[40 + 1];
    char *pLine = NULL;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    pFile = fopen(argv[1], "rt");

    for (;;)
    {
        memset(buf, 'X', sizeof(buf));
        errno = 0;
        pLine = fgets(buf, sizeof(buf), pFile);
        if (!pLine)
        {
            int subErrno = errno;
            if (feof(pFile))
            {
                break;
            }
            fprintf(stderr, "fgets: %s", strerror(subErrno));
            fprintf(stderr, "errno: %d\n", subErrno);
            goto EXIT_FUNC;
        }
        printf("----------\n");
        dumpArray(buf, sizeof(buf));
    }

    result = EXIT_SUCCESS;

EXIT_FUNC:
    if (pFile)
    {
        fclose(pFile);
    }

    return result;
}
