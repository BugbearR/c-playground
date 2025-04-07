#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

int main(int argc, char *argv[])
{
    int inTempError;
//    char buf[4096];
    char *buf = NULL;

    buf = (char *)malloc(4096);
    if (buf == NULL)
    {
        perror("malloc");
        return EXIT_FAILURE;
    }

    time_t start = time(NULL);
    long long counter = 0;
    int s = 0;
    while (difftime(time(NULL), start) < 10.0)
    {
        memset(buf, counter & 0xff, sizeof(buf));
        s += buf[1];
        counter++;
    };

    printf("Count (10 sec): %lld\n", counter);
    printf("Count per second: %lld\n", counter / 10);
    printf("operation elaps (ns): %f\n", 10000000000.0 / counter);
    printf("Sum: %d\n", s);
    free(buf);
    buf = NULL;

    return EXIT_SUCCESS;
}
