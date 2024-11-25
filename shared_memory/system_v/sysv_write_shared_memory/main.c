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

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <shmid> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    shmid = atoi(argv[1]);
    str = argv[2];

    addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1)
    {
        perror("shmat");
        return EXIT_FAILURE;
    }

    size = strlen(str);

    *(uint32_t *)addr = (uint32_t)size;
    addr += sizeof(uint32_t);
    memcpy(addr, str, strlen(str));

    return EXIT_SUCCESS;
}
