#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int r;
    if (argc < 2) {
        fprintf(stderr, "usage: %s number\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    errno = 0;
    r = atoi(argv[1]);
    if (r == 0) {
        if (errno != 0) {
            perror("atoi");
            exit(EXIT_FAILURE);
        }
    }
    printf("%d\n", r);
    return EXIT_SUCCESS;
}
