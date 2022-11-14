#ifndef CPLAYGROUND_IO_H_
#define CPLAYGROUND_IO_H_

#if HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>

/**
 * @brief Write exaxt bytes
 *
 * @param fd - file descriptor
 * @param pBuf - buffer to write
 * @param bufLen - buffer length
 * @param[out] pResultLen - result length
 * @retval 0 no error
 * @retval -1: error
 */
int cplayground_io_writeExact(int fd, const char *pBuf, size_t bufLen, size_t *pResultLen);

/**
 * @brief Read exaxt bytes
 *
 * @param fd - file descriptor
 * @param pBuf - buffer to write
 * @param bufLen - buffer length
 * @param[out] pResultLen - result length
 * @retval 0 no error
 * @retval -1: error
 */
int cplayground_io_readExact(int fd, const char *pBuf, size_t bufLen, size_t *pResultLen);

#endif /* CPLAYGROUND_IO_H_ */
