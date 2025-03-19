#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

typedef struct {
    pthread_spinlock_t writeWaitLock;
    pthread_rwlock_t rwlock;
    uint32_t size;
    char data[0];
} shared_data_t;

static volatile sig_atomic_t s_isStopRequested = 0;

void print_hex(const void *addr, size_t size)
{
    const unsigned char *p = addr;
    for (size_t i = 0; i < size; ++i)
    {
        printf(" %02x", p[i]);
    }
    printf("\n");
}

void mySignalHandler(int sigNo, siginfo_t *pInfo, void *pCtx)
{
    s_isStopRequested = 1;
}

int main(int argc, char *argv[])
{
    int shmid;
    const char *str;
    int size;
    shared_data_t *addr;
    int rc;
    struct sigaction sa = {0};

    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <shmid> <string1> <string2>\n", argv[0]);
        return EXIT_FAILURE;
    }

    shmid = atoi(argv[1]);
    addr = shmat(shmid, NULL, 0);
    if (addr == (void *)-1)
    {
        perror("shmat");
        return EXIT_FAILURE;
    }
    printf("shmat: %p\n", addr);

    sa.sa_sigaction = mySignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    printf("rwlock:\n");
    print_hex(&(addr->rwlock), sizeof(addr->rwlock));

    int flg = 0;
    while (!s_isStopRequested) {
        printf("writeWaitLock:\n");
        print_hex((const void *)&(addr->writeWaitLock), sizeof(addr->writeWaitLock));
        printf("spin lock\n");
        fflush(stdout);
        rc = pthread_spin_lock(&(addr->writeWaitLock));
        if (rc != 0)
        {
            fprintf(stderr, "pthread_spin_lock: %d %s\n", rc, strerror(rc));
            return EXIT_FAILURE;
        }
        printf("writeWaitLock:\n");
        print_hex((const void *)&(addr->writeWaitLock), sizeof(addr->writeWaitLock));

        printf("wrlock lock\n");
        fflush(stdout);
        rc = pthread_rwlock_wrlock(&(addr->rwlock));
        if (rc != 0)
        {
            fprintf(stderr, "pthread_rwlock_wrlock: %d %s\n", rc, strerror(rc));
            return EXIT_FAILURE;
        }
        printf("wrlock locked\n");
        fflush(stdout);
        print_hex(&(addr->rwlock), sizeof(addr->rwlock));

        sleep(3);

        str = argv[flg ? 2 : 3];
        flg = !flg;

        size = strlen(str);

        addr->size = size;
        memcpy(addr->data, str, size);

        printf("copy %.*s\n", (int)size, str);

        printf("wrlock unlock\n");
        fflush(stdout);
        rc = pthread_rwlock_unlock(&(addr->rwlock));
        if (rc != 0)
        {
            fprintf(stderr, "pthread_rwlock_unlock: %d %s\n", rc, strerror(rc));
            return EXIT_FAILURE;
        }
        printf("wrlock unlocked\n");
        fflush(stdout);
        printf("rwlock:\n");
        print_hex(&(addr->rwlock), sizeof(addr->rwlock));

        printf("writeWaitLock:\n");
        print_hex((const void *)&(addr->writeWaitLock), sizeof(addr->writeWaitLock));
        printf("spin unlock\n");
        fflush(stdout);
        rc = pthread_spin_unlock(&(addr->writeWaitLock));
        if (rc != 0)
        {
            fprintf(stderr, "pthread_spin_unlock: %d %s\n", rc, strerror(rc));
            return EXIT_FAILURE;
        }
        printf("spin unlocked\n");
        printf("writeWaitLock:\n");
        print_hex((const void *)&(addr->writeWaitLock), sizeof(addr->writeWaitLock));

        sleep(3);
    }

    return EXIT_SUCCESS;
}
