#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int shmid;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <shmid>\n", argv[0]);
        return EXIT_FAILURE;
    }

    shmid = atoi(argv[1]);
    if (shmctl(shmid, IPC_RMID, NULL) != 0)
    {
        perror("shmctl");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
