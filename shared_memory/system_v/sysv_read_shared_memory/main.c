#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int shmid;
    const char *str;
    int size;
    char *addr;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <shmid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    shmid = atoi(argv[1]);

    addr = shmat(shmid, NULL, SHM_RDONLY);
    if (addr == (void *)-1)
    {
        perror("shmat");
        return EXIT_FAILURE;
    }

    size = *(uint32_t *)addr;
    addr += sizeof(uint32_t);
    printf("Data size: %d\n", (int)size);
    printf("Data: %.*s\n", (int)size, addr);

    return EXIT_SUCCESS;
}
