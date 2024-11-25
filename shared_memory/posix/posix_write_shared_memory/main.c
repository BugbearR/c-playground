#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const char *name;
    char *addr;
    char *str;
    mode_t oflag;
    size_t size;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <name> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    oflag = O_RDWR;

    name = argv[1];
    str = argv[2];

    size = sizeof(uint32_t) + strlen(str);

    int fd = shm_open(name, oflag, 0);
    if (fd == -1)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    addr = mmap(NULL, size, PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return EXIT_FAILURE;
    }

    *(uint32_t *)addr = (uint32_t)size;
    addr += sizeof(uint32_t);
    memcpy(addr, str, strlen(str));

    if (close(fd) != 0)
    {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
