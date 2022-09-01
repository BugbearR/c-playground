#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump(char *p, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
    {
        printf(" %02hhx", p[i]);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "usage: %s string size\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *pEnd = NULL;
    uintmax_t sizeWk = strtoumax(argv[2], &pEnd, 10);
    if (sizeWk == 0 || sizeWk == UINTMAX_MAX)
    {
        if (errno != 0)
        {
            fprintf(stderr, "invalid size\n");
            return EXIT_FAILURE;
        }
    }
    if (*pEnd != '\0')
    {
        fprintf(stderr, "invalid size\n");
        return EXIT_FAILURE;
    }
    if (sizeWk > SIZE_MAX - 1)
    {
        fprintf(stderr, "invalid size\n");
        return EXIT_FAILURE;
    }
    size_t size = sizeWk;
    size_t argv1Len = strlen(argv[1]);
    size_t bufLen = ((size < argv1Len) ? argv1Len : size) + 1;

    char *pBuf = malloc(bufLen);
    if (!pBuf)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }
    memset(pBuf, 'x', bufLen);
    memcpy(pBuf, argv[1], argv1Len + 1);

    printf("%zu\n", strnlen(pBuf, size));
    dump(pBuf, size + 1);
    printf("\n");

    free(pBuf);

    return EXIT_SUCCESS;
}
