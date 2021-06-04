#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int subResult;
    if (argc < 2) {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }
    subResult = unlink(argv[1]);
    if (subResult != 0) {
        int subErrno = errno;
        perror("unlink");
        fprintf(stderr, "errno: %d\n", subErrno);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
