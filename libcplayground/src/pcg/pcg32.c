// Original LICENSE
// see https://www.pcg-random.org/download.html
// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

#include "cplayground/pcg.h"

#include <inttypes.h>

void cplayground_pcg32_init(cplayground_pcg32_t *pThis, uint64_t state, uint64_t inc)
{
    pThis->state = state;
    pThis->inc = inc;
}

uint32_t cplayground_pcg32_next(cplayground_pcg32_t *pThis)
{
    uint64_t oldstate = pThis->state;
    // Advance internal state
    pThis->state = oldstate * UINT64_C(0x5851f42d4c957f2d) + (pThis->inc | 1);
    // Calculate output function (XSH RR), uses old state for max ILP
    uint32_t xorshifted = (uint32_t)(((oldstate >> 18u) ^ oldstate) >> 27u);
    uint32_t rot = (uint32_t)(oldstate >> 59u);
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}
