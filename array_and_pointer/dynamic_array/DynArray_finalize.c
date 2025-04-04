#include "DynArray.h"

void DynArray_finalize(DynArray_t *pThis)
{
    if (pThis == NULL) {
        return;
    }

    if (pThis->data != NULL) {
        if (pThis->allocateFn != NULL) {
            pThis->allocateFn(pThis->data, 0);
        }
        pThis->data = NULL;
    }

    pThis->size = 0;
    pThis->capacity = 0;
    pThis->elementSize = 0;
    pThis->allocateFn = NULL;
}
