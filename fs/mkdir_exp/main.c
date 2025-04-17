#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int ret;
    int myerrno;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *dirPath = argv[1];
    ret = mkdir(dirPath, 0755);
    if (ret != 0) {
        myerrno = errno;
        perror("mkdir");
        printf("errno = %d\n", myerrno);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
