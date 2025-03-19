#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <pthread.h>

typedef struct {
    pthread_spinlock_t writeWaitLock;
    pthread_rwlock_t rwlock;
    uint32_t size;
    char data[0];
} shared_data_t;

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

void print_hex(const void *addr, size_t size)
{
    const unsigned char *p = addr;
    for (size_t i = 0; i < size; ++i)
    {
        printf(" %02x", p[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    key_t key;
    size_t size;
    shared_data_t *addr;
    int rc;
    pthread_rwlockattr_t attr;

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

    addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1)
    {
        perror("shmat");
        return EXIT_FAILURE;
    }
    printf("shmat: %p\n", addr);

    rc = pthread_spin_init(&addr->writeWaitLock, PTHREAD_PROCESS_SHARED);
    if (rc != 0) {
        fprintf(stderr, "pthread_spin_init: %d %s\n", rc, strerror(rc));
        return EXIT_FAILURE;
    }
    printf("writeWaitLock:\n");
    print_hex((const void *)&(addr->writeWaitLock), sizeof(addr->writeWaitLock));

    rc = pthread_rwlockattr_init(&attr);
    if (rc != 0) {
        fprintf(stderr, "pthread_rwlockattr_init: %d %s\n", rc, strerror(rc));
        return EXIT_FAILURE;
    }

    rc = pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    if (rc != 0) {
        fprintf(stderr, "pthread_rwlockattr_setpshared: %d %s\n", rc, strerror(rc));
        return EXIT_FAILURE;
    }

    rc = pthread_rwlock_init(&(addr->rwlock), &attr);
    if (rc != 0) {
        fprintf(stderr, "pthread_rwlock_init: %d %s\n", rc, strerror(rc));
        return EXIT_FAILURE;
    }

    addr->size = 0;
    memset(addr->data, 0, sizeof(addr->data));

    printf("rwlock:\n");
    print_hex(&(addr->rwlock), sizeof(pthread_rwlock_t));

    printf("shmid: %d\n", shmid);
    return EXIT_SUCCESS;
}
