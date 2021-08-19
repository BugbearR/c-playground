#define _XOPEN_SOURCE

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main(int argc, char *argv[])
{
    int subResult;
    time_t t;
    struct tm tm;
    const char *pEnd;

    memset(&tm, 0x01, sizeof(tm)); // dirty data

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s format value\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t len = strlen(argv[2]);
    pEnd = strptime(argv[2], argv[1], &tm);
    if (pEnd == NULL)
    {
        printf("Warning: NULL returned from strptime.\n");
    }
    else if (pEnd != argv[2] + len)
    {
        printf("Warning: strptime did not parse to end.\n");
        printf("start:%p\n", argv[2]);
        printf("pEnd:%p\n", pEnd);
        printf("diff:%td\n", pEnd - argv[2]);
        printf("left:\"%s\"\n", pEnd);
    }

    printf("dump tm\n");
    dumpTm(&tm);
    printf("\n");

    return EXIT_SUCCESS;
}
