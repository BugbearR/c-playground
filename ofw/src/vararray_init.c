#include "ofw/vararray.h"

void Ofw_VarArray_init(Ofw_VarArray_t *pThis, int32_t length, int32_t elementSize, void *pBuf)
{
    pThis->length = length;
    pThis->elementSize = elementSize;
    pThis->pBuf = (uint8_t *)pBuf;
}
