#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    const char *name;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    name = argv[1];

    if (shm_unlink(name) != 0)
    {
        perror("shm_unlink");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
