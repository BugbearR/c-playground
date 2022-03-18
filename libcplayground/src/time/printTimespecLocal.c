#include "cplayground/time.h"

void cplayground_printTimespecLocal(struct timespec *pTimespec)
{
    cplayground_fprintTimespecLocal(stdout, pTimespec);
}
