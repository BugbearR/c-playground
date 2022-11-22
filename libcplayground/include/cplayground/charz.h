#ifndef CPLAYGROUND_CHARZ_H_
#define CPLAYGROUND_CHARZ_H_

#if HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>
#include <stdbool.h>

bool cplayground_charz_isBlank(const char *p);

bool cplayground_charz_isEmpty(const char *p);

size_t cplayground_charz_length(const char *p);

char *cplayground_charz_trimEnd(char *p);

char *cplayground_charz_trimStart(char *p);

// char *cplayground_trimEnd(char *p, size_t bufLen);

char *cplayground_charz_copy(char *pDst, size_t dstLen, const char *pSrc);

char *cplayground_charz_copyLimit(char *pDst, size_t dstLen, const char *pSrc, size_t srcLen);

#endif /* CPLAYGROUND_CHARZ_H_ */
