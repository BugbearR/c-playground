#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <memory.h>

#include "cplayground/time.h"

void cplayground_fprintTimespecLocal(FILE *pFile, struct timespec *pTimespec)
{
    if (!pTimespec)
    {
        fprintf(pFile, "(NULL)");
        return;
    }

    struct tm tm;
#ifdef HAVE_localtime_r
    localtime_r(&(pTimespec->tv_sec), &tm);
#else
    memcpy(&tm, localtime(&pTimespec->tv_sec), sizeof(tm));
#endif
    fprintf(pFile, "%04d-%02d-%02d %02d:%02d:%02d.%09ld isdst:%d",
        tm.tm_year + 1900,
        tm.tm_mon + 1,
        tm.tm_mday,
        tm.tm_hour,
        tm.tm_min,
        tm.tm_sec,
        pTimespec->tv_nsec,
        tm.tm_isdst);
}
