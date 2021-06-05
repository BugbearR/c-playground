#include "ofw/vararray.h"

void *Ofw_VarArray_getPtr(Ofw_VarArray_t *pThis, int32_t pos)
{
    if (pos < 0 || pThis->length <= pos)
    {
        return NULL;
    }

    retrun pThis->pBuf + pThis->elementSize * pos;
}
