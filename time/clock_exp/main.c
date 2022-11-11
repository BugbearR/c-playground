#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo() {
    return rand();
}

int main(int argc, char *argv[])
{
    clock_t s;
    clock_t e;

    if (argc < 2) {
        fprintf(stderr, "usage: %s count\n", argv[0]);
        return EXIT_FAILURE;
    }

    time_t t = time(NULL);
    srand((unsigned int)t);

    int count = atoi(argv[1]);

    s = clock();

    // something process
    int sum = 0;
    int i;
    for (i = 0; i < count; i++) {
        sum += foo();
    }

    e = clock();

    printf("%d\n", sum);

    printf("elaps: %f\n", ((double)(e - s)) / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
