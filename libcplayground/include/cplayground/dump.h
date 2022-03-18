#ifndef CPLAYGROUND_DUMP_H_
#define CPLAYGROUND_DUMP_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>

void cplayground_dump(const void *pBuf, size_t bufLen);

void cplayground_dumpWithAddr(const void *pBuf, size_t bufLen);

#endif /* CPLAYGROUND_DUMP_H_ */
