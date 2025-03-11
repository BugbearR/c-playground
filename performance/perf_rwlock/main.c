#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    pthread_rwlockattr_t attr;
    pthread_rwlock_t rwlock;
    int inTempError;

    /* Read/Writeロックの属性オブジェクトを初期化 */
    inTempError = pthread_rwlockattr_init(&attr);
    if (inTempError != 0) {
        printf("pthread_rwlockattr_init: %s\n", strerror(inTempError));
        printf("Error: %d\n", inTempError);
        return EXIT_FAILURE;
    }

    inTempError = pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    if (inTempError != 0) {
        printf("pthread_rwlockattr_setpshared: %s\n", strerror(inTempError));
        printf("Error: %d\n", inTempError);
        return EXIT_FAILURE;
    }

    inTempError = pthread_rwlock_init(&rwlock, &attr);
    if (inTempError != 0) {
        printf("pthread_rwlock_init: %s\n", strerror(inTempError));
        printf("Error: %d\n", inTempError);
        return EXIT_FAILURE;
    }

     inTempError = pthread_rwlockattr_destroy(&attr);
    if (inTempError != 0) {
        printf("pthread_rwlockattr_destroy: %s\n", strerror(inTempError));
        printf("Error: %d\n", inTempError);
        return EXIT_FAILURE;
    }

    time_t start = time(NULL);
    long long counter = 0;
    while (difftime(time(NULL), start) < 10.0)
    {
        inTempError = pthread_rwlock_rdlock(&rwlock);
        if (inTempError != 0) {
            printf("pthread_rwlock_rdlock: %s\n", strerror(inTempError));
            printf("Error: %d\n", inTempError);
            return EXIT_FAILURE;
        }
        inTempError = pthread_rwlock_unlock(&rwlock);
        if (inTempError != 0) {
            printf("pthread_rwlock_unlock: %s\n", strerror(inTempError));
            printf("Error: %d\n", inTempError);
            return EXIT_FAILURE;
        }

        counter++;
    };

    printf("Count (10 sec): %lld\n", counter);
    printf("Count per second: %lld\n", counter / 10);
    printf("operation elaps (ns): %f\n", 10000000000.0 / counter);

    inTempError = pthread_rwlock_destroy(&rwlock);
    if (inTempError != 0) {
        printf("pthread_rwlock_destroy: %s\n", strerror(inTempError));
        printf("Error: %d\n", inTempError);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
