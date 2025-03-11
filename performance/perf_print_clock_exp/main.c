#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    time_t start = time(NULL);
    time_t t;
    long long counter = 0;
    while (difftime((t = time(NULL)), start) < 10.0)
    {
        struct timespec ts;
        clock_gettime(CLOCK_REALTIME, &ts);
        struct tm *tm = localtime(&ts.tv_sec);
        printf("%04d-%02d-%02d %02d:%02d:%02d.%09ld\n",
               tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
               tm->tm_hour, tm->tm_min, tm->tm_sec, ts.tv_nsec);
        counter++;
    };

    printf("Count (10 sec): %lld\n", counter);
    printf("Count per second: %lld\n", counter / 10);
    printf("operation elaps (ns): %f\n", 10000000000.0 / counter);

    return EXIT_SUCCESS;
}
