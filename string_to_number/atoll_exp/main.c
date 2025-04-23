#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

int main(int argc, char *argv[]) {
    long long r;
    int myErrno;
    if (argc < 2) {
        fprintf(stderr, "usage: %s number_string\n", argv[0]);
        return EXIT_FAILURE;
    }
    r = atoll(argv[1]);
    myErrno = errno;
    if (errno != 0) {
        perror("atoll");
    }
    printf("result: %ld\n", r);
    printf("errno: %d\n", myErrno);
    return EXIT_SUCCESS;
}
