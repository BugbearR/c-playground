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

// char *cplayground_trimEnd(char *p);

// char *cplayground_trimEnd(char *p, size_t bufLen);

#endif /* CPLAYGROUND_STRING_H_ */
