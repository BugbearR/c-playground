#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

int main(int argc, char *argv[])
{
    int subResult;
    struct timespec ts;
    struct tm *pTm;
    clock_t clockType;

    if (argc < 2) {
        fprintf(stderr, "usage: %s clockType\n", argv[0]);
        fprintf(stderr, "clockType\n");

#ifdef CLOCK_REALTIME
        fprintf(stderr, "A: CLOCK_REALTIME\n");
#endif
#ifdef CLOCK_REALTIME_COARSE
        fprintf(stderr, "B: CLOCK_REALTIME_COARSE\n");
#endif
#ifdef CLOCK_MONOTONIC
        fprintf(stderr, "C: CLOCK_MONOTONIC\n");
#endif
#ifdef CLOCK_MONOTONIC_COARSE
        fprintf(stderr, "D: CLOCK_MONOTONIC_COARSE\n");
#endif
#ifdef CLOCK_MONOTONIC_RAW
        fprintf(stderr, "E: CLOCK_MONOTONIC_RAW\n");
#endif
#ifdef CLOCK_BOOTTIME
        fprintf(stderr, "F: CLOCK_BOOTTIME\n");
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
        fprintf(stderr, "G: CLOCK_PROCESS_CPUTIME_ID\n");
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
        fprintf(stderr, "H: CLOCK_PROCESS_CPUTIME_ID\n");
#endif
        return EXIT_FAILURE;
    }

    switch (argv[1][0]) {
#ifdef CLOCK_REALTIME
    case 'A':
        clockType = CLOCK_REALTIME;
        break;
#endif
#ifdef CLOCK_REALTIME_COARSE
    case 'B':
        clockType = CLOCK_REALTIME_COARSE;
        break;
#endif
#ifdef CLOCK_MONOTONIC
    case 'C':
        clockType = CLOCK_MONOTONIC;
        break;
#endif
#ifdef CLOCK_MONOTONIC_COARSE
    case 'D':
        clockType = CLOCK_MONOTONIC_COARSE;
        break;
#endif
#ifdef CLOCK_MONOTONIC_RAW
    case 'E':
        clockType = CLOCK_MONOTONIC_RAW;
        break;
#endif
#ifdef CLOCK_BOOTTIME
    case 'F':
        clockType = CLOCK_BOOTTIME;
        break;
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
    case 'G':
        clockType = CLOCK_PROCESS_CPUTIME_ID;
        break;
#endif
#ifdef CLOCK_PROCESS_CPUTIME_ID
    case 'H':
        clockType = CLOCK_PROCESS_CPUTIME_ID;
        break;
#endif
    default:
        fprintf(stderr, "unknown clock type.");
    }

    subResult = clock_getres(clockType, &ts);
    if (subResult != 0)
    {
        perror("clock_getres");
        return EXIT_FAILURE;
    }
    printf("%" PRIdMAX ".%09" PRIdMAX "\n", (intmax_t)ts.tv_sec, (intmax_t)ts.tv_nsec);

    return EXIT_SUCCESS;
}
