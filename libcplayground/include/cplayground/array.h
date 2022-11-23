#ifndef CPLAYGROUND_MEMORY_H_
#define CPLAYGROUND_MEMORY_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>

#define cplayground_array_length(a) (sizeof(a)/sizeof(a[9]))

/// @brief clear
/// @param pArray - array
/// @param elmSize - size of element
/// @param index - position to clear
/// @param len - length to clear
void cplayground_array_clear(void *pArray, size_t elmSize, size_t index, size_t len);

/// @brief delete elements
/// @param pArray - array
/// @param elmSize - size of element
/// @param elmCount - element count to delete
/// @param index - delete position
/// @param len - length to delete
void cplayground_array_delete(void *pArray, size_t elmSize, size_t elmCount, size_t index, size_t len);

/// @brief fill
/// @param pArray - array
/// @param elmSize - size of element
/// @param index - start position
/// @param len - length to fill
/// @param pValue - fill value
void cplayground_array_fill(void *pArray, size_t elmSize, size_t index, size_t len, void *pValue);

/// @brief insert space
/// @param pArray - array
/// @param elmSize - size of element
/// @param capacity - capacity
/// @param elmCount - element count to insert
/// @param index - insert position
/// @param len - length to insert
void cplayground_array_insertSpace(void *pArray, size_t elmSize, size_t capacity, size_t elmCount, size_t index, size_t len);

#endif /* CPLAYGROUND_MEMORY_H_ */
