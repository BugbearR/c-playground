#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    int r;
    int myErrno;
    if (argc < 2) {
        fprintf(stderr, "usage: %s number_string\n", argv[0]);
        return EXIT_FAILURE;
    }
    r = atoi(argv[1]);
    myErrno = errno;
    if (errno != 0) {
        perror("atoi");
    }
    printf("result: %d\n", r);
    printf("errno: %d\n", myErrno);
    return EXIT_SUCCESS;
}
