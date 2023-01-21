#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int foo() {
    return rand();
}


void addTimespec(struct timespec *p1, struct timespec *p2, struct timespec *pOut)
{
    if (p1->tv_nsec + p2->tv_nsec < 1000000000L) {
        pOut->tv_nsec = p1->tv_nsec + p2->tv_nsec;
        pOut->tv_sec = p1->tv_sec + p2->tv_sec;
    }
    else {
        pOut->tv_nsec = p1->tv_nsec + p2->tv_nsec - 1000000000L;
        pOut->tv_sec = p1->tv_sec + p2->tv_sec + 1;
    }
}

void subTimespec(struct timespec *p1, struct timespec *p2, struct timespec *pOut)
{
    if (p1->tv_nsec >= p2->tv_nsec) {
        pOut->tv_nsec = p1->tv_nsec - p2->tv_nsec;
        pOut->tv_sec = p1->tv_sec - p2->tv_sec;
    }
    else {
        pOut->tv_nsec = p1->tv_nsec + (1000000000L - p2->tv_nsec);
        pOut->tv_sec = p1->tv_sec - p2->tv_sec - 1;
    }
}

int main(int argc, char *argv[])
{
    struct timespec s;
    struct timespec e;
    struct timespec d;
    struct timespec total;
    int subResult;

    if (argc < 3) {
        fprintf(stderr, "usage: %s outerCount innerCount\n", argv[0]);
        return EXIT_FAILURE;
    }

    time_t t = time(NULL);
    srand((unsigned int)t);

    int outerCount = atoi(argv[1]);
    int inner_count = atoi(argv[2]);

    subResult = clock_gettime(CLOCK_MONOTONIC, s);
    if (subResult != 0) {
        perror("clock_gettime");
        return EXIT_FAILURE;
    }

    // something process
    int sum = 0;
    int i;
    for (i = 0; i < outerCount; i++) {
        int j;

        subResult = clock_gettime(CLOCK_MONOTONIC, &s);
        if (subResult != 0) {
            perror("clock_gettime");
            return EXIT_FAILURE;
        }

        for (j = 0; j < inner_count; j++) {
            sum += foo();
        }

        subResult = clock_gettime(CLOCK_MONOTONIC, &e);
        if (subResult != 0) {
            perror("clock_gettime");
            return EXIT_FAILURE;
        }

        subtimespec(&e, &s, &d);
        addTimespec(&total, &d, &total);
    }

    e = clock();

    printf("%d\n", sum);

    printf("elaps: %d.%09d\n", total.((double)(e - s)) / CLOCKS_PER_SEC);
    return EXIT_SUCCESS;
}
