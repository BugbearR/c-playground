#include "cplayground/xorshift.h"

void cplayground_xorshift32_init(cplayground_xorshift32_t *pThis, uint32_t seed)
{
    pThis->a = seed;
}

uint32_t cplayground_xorshift32_next(cplayground_xorshift32_t *pThis)
{
    uint32_t t = pThis->a;
    t ^= t << 13;
    t ^= t >> 17;
    t ^= t << 5;
    pThis->a = t;
    return t;
}
