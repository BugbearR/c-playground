#ifndef CPLAYGROUND_PCG_H_
#define CPLAYGROUND_PCG_H_

// Original LICENSE
// see https://www.pcg-random.org/download.html
// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

typedef struct cplayground_pcg32_tag {
    uint64_t state;
    uint64_t inc;
} cplayground_pcg32_t;

void cplayground_pcg32_init(cplayground_pcg32_t *pThis, uint64_t state, uint64_t inc);

uint32_t cplayground_pcg32_next(cplayground_pcg32_t *pThis);

#endif /* CPLAYGROUND_PCG_H_ */
