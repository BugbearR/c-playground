#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t start = time(NULL);
    long long counter = 0;
    while (difftime(time(NULL), start) < 10.0)
    {
        counter++;
    };

    printf("Count (10 sec): %lld\n", counter);
    printf("Count per second: %lld\n", counter / 10);
    printf("operation elaps (ns): %f\n", 10000000000.0 / counter);

    return EXIT_SUCCESS;
}
