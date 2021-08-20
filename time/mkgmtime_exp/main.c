//#define _XOPEN_SOURCE

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

void dumpTm(struct tm *pTm)
{
    printf("tm_year: %d\n", pTm->tm_year);
    printf("tm_mon: %d\n", pTm->tm_mon);
    printf("tm_mday: %d\n", pTm->tm_mday);
    printf("tm_hour: %d\n", pTm->tm_hour);
    printf("tm_min: %d\n", pTm->tm_min);
    printf("tm_sec: %d\n", pTm->tm_sec);
    printf("tm_wday: %d\n", pTm->tm_wday);
    printf("tm_yday: %d\n", pTm->tm_yday);
    printf("tm_isdst: %d\n", pTm->tm_isdst);
}

time_t mkgmtime(struct tm *tm) {
    time_t result;
    char *pOrgTz = NULL;

    /* backup TZ */
    pOrgTz = getenv("TZ");
    if (pOrgTz) {
        pOrgTz = strdup(pOrgTz);
    }

    /* Set UTC to TZ */
    setenv("TZ", "", 1);
    tzset();

    result = mktime(tm);

    /* restore TZ */
    if (pOrgTz) {
        setenv("TZ", pOrgTz, 1);
        free(pOrgTz);
    }
    else {
        unsetenv("TZ");
    }
    tzset();

    return result;
}

int main(int argc, char *argv[])
{
    int subResult;
    time_t t;
    struct tm tm;

    if (argc < 8)
    {
        fprintf(stderr, "usage: %s tm_year tm_mon tm_mday tm_hour tm_min tm_sec tm_isdst\n", argv[0]);
        return EXIT_FAILURE;
    }

    tm.tm_year = atoi(argv[1]);
    tm.tm_mon = atoi(argv[2]);
    tm.tm_mday = atoi(argv[3]);
    tm.tm_hour = atoi(argv[4]);
    tm.tm_min = atoi(argv[5]);
    tm.tm_sec = atoi(argv[6]);
    tm.tm_isdst = atoi(argv[7]);

    errno = 0;
    t = mkgmtime(&tm);
    int myErrno = errno;
    printf("%s\n", strerror(myErrno));

    printf("t: %" PRIdMAX "\n", (intmax_t)t);

    printf("localtime\n");
    dumpTm(localtime(&t));
    printf("\n");

    printf("gmtime\n");
    dumpTm(gmtime(&t));
    printf("\n");

    return EXIT_SUCCESS;
}
