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

    subResult = clock_gettime(clockType, &ts);
    printf("%" PRIdMAX ".%09" PRIdMAX "\n", (intmax_t)ts.tv_sec, (intmax_t)ts.tv_nsec);

    printf("ctime:%s\n", ctime(&ts.tv_sec));

    pTm = localtime(&ts.tv_sec);
    printf("localtime\n");
    printf("tm_year:%d\n", pTm->tm_year);
    printf("tm_mon:%d\n", pTm->tm_mon);
    printf("tm_mday:%d\n", pTm->tm_mday);
    printf("tm_hour:%d\n", pTm->tm_hour);
    printf("tm_min:%d\n", pTm->tm_min);
    printf("tm_sec:%d\n", pTm->tm_sec);
    printf("tm_wday:%d\n", pTm->tm_wday);
    printf("tm_yday:%d\n", pTm->tm_yday);
    printf("tm_isdst:%d\n", pTm->tm_isdst);
    printf("asctime:%s\n", asctime(pTm));
    printf("\n");

    pTm = gmtime(&ts.tv_sec);
    printf("gmtime\n");
    printf("tm_year:%d\n", pTm->tm_year);
    printf("tm_mon:%d\n", pTm->tm_mon);
    printf("tm_mday:%d\n", pTm->tm_mday);
    printf("tm_hour:%d\n", pTm->tm_hour);
    printf("tm_min:%d\n", pTm->tm_min);
    printf("tm_sec:%d\n", pTm->tm_sec);
    printf("tm_wday:%d\n", pTm->tm_wday);
    printf("tm_yday:%d\n", pTm->tm_yday);
    printf("tm_isdst:%d\n", pTm->tm_isdst);
    printf("asctime:%s\n", asctime(pTm));
    printf("\n");

    return EXIT_SUCCESS;
}
