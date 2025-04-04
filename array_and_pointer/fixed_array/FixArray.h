#ifndef FIXARRAY_H_
#define FIXARRAY_H_

#include <stddef.h>

typedef struct FixArray
{
    void *pArray;
    size_t elementSize;
    size_t size;
} FixArray_t;

void FixArray_initialize(FixArray_t *pFixArray, size_t elementSize, size_t size);

#endif // FIXARRAY_H_
