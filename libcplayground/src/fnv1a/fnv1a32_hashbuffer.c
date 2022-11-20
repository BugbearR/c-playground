#include <cplayground/fnv1a.h>

#include "fnv1a_local.h"

uint32_t cplayground_fnv1a32_hashBuffer(void *pBuf, size_t bufLen)
{
    uint32_t h = FNV1A_HASH32_OFFSET;
    for (uint8_t *p = pBuf, *pEnd = pBuf + bufLen; p < pEnd; p++)
    {
        h = (h ^ (uint32_t)*p) * FNV1A_HASH32_PRIME;
    }
    return h;
}
