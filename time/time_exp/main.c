#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

int main(void)
{
    time_t t;
    struct tm *pTm;

    time(&t);
    printf("%" PRIdMAX "\n", (intmax_t)t);

    printf("ctime:%s\n", ctime(&t));

    pTm = localtime(&t);
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

    pTm = gmtime(&t);
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
