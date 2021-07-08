#if !defined Ofw_VarArray_H_
#define Ofw_VarArray_H_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

#include "ofw/buffer.h"

typedef struct Ofw_VarArray_tag
{
    int32_t elementSize;
    int32_t length;
    Ofw_Buffer_t *pBuffer;
} Ofw_VarArray_t;

void Ofw_VarArray_init(Ofw_VarArray_t *pThis, int32_t elementSize, int32_t length, Ofw_Buffer_t *pBuffer);

void *Ofw_VarArray_getPtr(Ofw_VarArray_t *pThis, int32_t pos);

#endif /* Ofw_VarArray_H_ */
