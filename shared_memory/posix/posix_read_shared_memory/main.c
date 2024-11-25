#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdint.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    const char *name;
    char *addr;
    char str[100];
    mode_t oflag;
    size_t size;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <name> <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    oflag = O_RDONLY;

    name = argv[1];
    size = atoi(argv[2]);

    int fd = shm_open(name, oflag, 0);
    if (fd == -1)
    {
        perror("shm_open");
        return EXIT_FAILURE;
    }

    addr = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED)
    {
        perror("mmap");
        return EXIT_FAILURE;
    }

    uint32_t *dataLen = (uint32_t *)addr;
    addr += sizeof(uint32_t);
    printf("Data length: %" PRId32 "\n", *dataLen);
    printf("Data: %.*s\n", (int)*dataLen, addr);

    if (close(fd) != 0)
    {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
