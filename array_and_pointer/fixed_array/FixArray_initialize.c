#include "FixArray.h"

int FixArray_initialize(FixArray_t *pThis, void *pArray, size_t elementSize, size_t size)
{
    pThis->pArray = pArray;
    pThis->elementSize = elementSize;
    pThis->size = size;
}
