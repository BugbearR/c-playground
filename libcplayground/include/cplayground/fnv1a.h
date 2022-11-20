#ifndef CPLAYGROUND_FNV1A_H_
#define CPLAYGROUND_FNV1A_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>
#include <stddef.h>

typedef struct cplayground_fnv1a32_tag {
    uint32_t h;
} cplayground_fnv1a32_t;

/**
 * @brief FNV-1a hash function. initialize
 * @param[in,out] pThis - FNV-1a hash function object
 */
void cplayground_fnv1a32_init(cplayground_fnv1a32_t *pThis);

/**
 * @brief FNV-1a hash function. process next byte
 * @param[in,out] pThis - FNV-1a hash function object
 * @returns FNV-1a hash value
 */
uint32_t cplayground_fnv1a32_next(cplayground_fnv1a32_t *pThis, uint8_t c);

/**
 * @brief FNV-1a hash function
 * @param pBuf - buffer
 * @param bufLen - buffer length
 * @returns FNV-1a hash value
 */
uint32_t cplayground_fnv1a32_hashBuffer(void *pBuf, size_t bufLen);

#endif /* CPLAYGROUND_FNV1A_H_ */
