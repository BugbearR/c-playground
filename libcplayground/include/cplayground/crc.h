#ifndef CPLAYGROUND_CRC_H_
#define CPLAYGROUND_CRC_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>
#include <stddef.h>

/**
 * @brief CRC32 hunction
 * @param pBuf - buffer
 * @param bufLen - buffer length
 * @returns CRC32 value
 */
uint32_t cplayground_crc_crc32(void *pBuf, size_t bufLen);

#endif /* CPLAYGROUND_CRC_H_ */
