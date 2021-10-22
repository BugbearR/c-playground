#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <inttypes.h>

int main(void)
{
    int subResult;
    struct timeval tv;
    struct tm *pTm;

    subResult = gettimeofday(&tv, NULL);
    printf("%" PRIdMAX ".%06" PRIdMAX "\n", (intmax_t)tv.tv_sec, (intmax_t)tv.tv_usec);

    printf("ctime:%s\n", ctime(&tv.tv_sec));

    pTm = localtime(&tv.tv_sec);
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

    pTm = gmtime(&tv.tv_sec);
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
