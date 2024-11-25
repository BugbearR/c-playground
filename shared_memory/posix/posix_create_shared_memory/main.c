#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    const char *name;
    int oflag;
    mode_t mode;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <name> <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    oflag = O_CREAT | O_RDWR;

    name = argv[1];
    int size = atoi(argv[2]);

    int fd = shm_open(name, oflag, 0666);
    if (fd == -1)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    if (ftruncate(fd, size) == -1)
    {
        perror("ftruncate");
        return EXIT_FAILURE;
    }

    if (close(fd) != 0)
    {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
