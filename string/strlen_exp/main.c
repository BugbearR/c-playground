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
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s string\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("%zu\n", strlen(argv[1]));
    dump(argv[1], strlen(argv[1]) + 1);
    printf("\n");

    return EXIT_SUCCESS;
}
