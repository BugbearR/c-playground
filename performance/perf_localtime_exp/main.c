#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t start = time(NULL);
    time_t t;
    long long counter = 0;
    while (difftime((t = time(NULL)), start) < 10.0)
    {
        struct tm *tm = localtime(&t);
        counter++;
    };

    printf("Count (10 sec): %lld\n", counter);
    printf("Count per second: %lld\n", counter / 10);
    printf("operation elaps (ns): %f\n", 10000000000.0 / counter);

    return EXIT_SUCCESS;
}
