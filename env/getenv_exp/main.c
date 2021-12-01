#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *pEnv = NULL;

    if (argc < 2) {
        fprintf(stderr, "usage: %s name\n", argv[0]);
        return EXIT_FAILURE;
    }

    pEnv = getenv(argv[1]);
    if (!pEnv) {
        perror("getenv");
        printf("NULL\n");
    }
    else {
        printf("%s\n", pEnv);
    }

    return EXIT_SUCCESS;
}
