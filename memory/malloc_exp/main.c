#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    size_t length;
    sscanf(argv[1], "%zu", &length);

    char *pBuf = malloc(length);
    if (!pBuf)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }
    printf("%p\n", pBuf);
    free(pBuf);

    return EXIT_SUCCESS;
}
