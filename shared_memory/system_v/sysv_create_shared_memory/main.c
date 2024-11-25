#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>

int isinteger(const char *str)
{
    while (*str)
    {
        if (!isdigit(*str))
        {
            return 0;
        }
        ++str;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    key_t key;
    size_t size;

    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s <key> <size>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // IPC_PRIVATE (0) is a special key that tells the system to generate a new key
    if (strcmp(argv[1], "IPC_PRIVATE") == 0)
    {
        key = IPC_PRIVATE;
    }
    else if (isinteger(argv[1]))
    {
        key = atoi(argv[1]); // Be careful, key is not always int
    }
    else
    {
        key = ftok(argv[1], 1);
        if (key == -1)
        {
            perror("ftok");
            return EXIT_FAILURE;
        }
        printf("key: %d\n", (int)key); // Be careful, key is not always int
    }

    size = atoi(argv[2]);

//#define IPC_CREAT	01000		/* Create key if key does not exist. */
//#define IPC_EXCL	02000		/* Fail if key exists.  */
//#define IPC_NOWAIT	04000		/* Return error on wait.  */

    int shmid = shmget(key, size, IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (shmid == -1)
    {
        perror("shmget");
        return EXIT_FAILURE;
    }

    printf("shmid: %d\n", shmid);
    return EXIT_SUCCESS;
}
