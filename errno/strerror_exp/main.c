#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s number\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int myErrno = atoi(argv[1]);
    printf("%s\n", strerror(myErrno));
    return EXIT_SUCCESS;
}
