#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cplayground/dump.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        cplayground_dump(argv[i], strlen(argv[i]) + 1);
        printf("\n");
        cplayground_dumpWithAddr(argv[i], strlen(argv[i]) + 1);
    }

    printf("OK\n");
    return EXIT_SUCCESS;
}
