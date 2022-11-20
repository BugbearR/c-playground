#include <stdint.h>
#include <stddef.h>

#include "cplayground/fnv1a.h"

#include "fnv1a_local.h"

void cplayground_fnv1a32_init(cplayground_fnv1a32_t *pThis)
{
    pThis->h = FNV1A_HASH32_OFFSET;
}

uint32_t cplayground_fnv1a32_next(cplayground_fnv1a32_t *pThis, uint8_t c)
{
    pThis->h = (pThis->h ^ (uint32_t)c) * FNV1A_HASH32_PRIME;
    return pThis->h;
}
