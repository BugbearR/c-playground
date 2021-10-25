#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int subResult;
    if (argc < 3) {
        fprintf(stderr, "usage: %s old_path new_path\n", argv[0]);
        return EXIT_FAILURE;
    }
    subResult = rename(argv[1], argv[2]);
    if (subResult != 0) {
        int subErrno = errno;
        perror("rename");
        fprintf(stderr, "errno: %d\n", subErrno);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
