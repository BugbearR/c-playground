#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    int myErrno;
    intmax_t r;
    char *pEnd = NULL;
    if (argc < 3) {
        fprintf(stderr, "usage: %s number_string base\n", argv[0]);
        return EXIT_FAILURE;
    }
    int base = atoi(argv[2]);
    errno = 0;
    r = strtoimax(argv[1], &pEnd, base);
    myErrno = errno;
    if (errno != 0) {
        perror("strtoimax");
    }
    printf("result: %" PRIdMAX "\n", r);
    printf("errno: %d\n", myErrno);
    printf("pEnd: %s\n", pEnd);
    return EXIT_SUCCESS;
}
