#ifndef CPLAYGROUND_XORSHIFT_H_
#define CPLAYGROUND_XORSHIFT_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

typedef struct cplayground_xorshift32_tag {
    uint32_t a;
} cplayground_xorshift32_t;

void cplayground_xorshift32_init(cplayground_xorshift32_t *pThis, uint32_t seed);

uint32_t cplayground_xorshift32_next(cplayground_xorshift32_t *pThis);

#endif /* CPLAYGROUND_XORSHIFT_H_ */
