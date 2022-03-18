#ifndef CPLAYGROUND_TIME_H_
#define CPLAYGROUND_TIME_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdio.h>
#include <time.h>

void cplayground_fprintTimespecLocal(FILE *pFile, struct timespec *pTimespec);

void cplayground_printTimespecLocal(struct timespec *pTimespec);

#endif /* CPLAYGROUND_TIME_H_ */
