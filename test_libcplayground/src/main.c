#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cplayground/dump.h>

int main(int argc, char *argv[])
{
    int i;

    for (i = 0; i < argc; i++) {
        // cplayground_dumpOut(argv[i], strlen(argv[i]) + 1);
        // printf("\n");
        cplayground_dumpOutWithAddr(argv[i], strlen(argv[i]) + 1);
    }

    printf("OK\n");
    return EXIT_SUCCESS;
}
