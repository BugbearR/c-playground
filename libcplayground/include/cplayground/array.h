#ifndef CPLAYGROUND_MEMORY_H_
#define CPLAYGROUND_MEMORY_H_

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stddef.h>

void cplayground_array_clear(void *p, size_t elmSize, size_t index, size_t len);

void cplayground_array_fill(void *p, size_t elmSize, size_t index, size_t len, void *pValue);

void cplayground_array_insert(void *p, size_t elmSize, size_t capacity, size_t elmCount, size_t index, size_t len);

void cplayground_array_delete(void *p, size_t elmSize, size_t elmCount, size_t index, size_t len);

#endif /* CPLAYGROUND_MEMORY_H_ */
