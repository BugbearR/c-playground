#include "DynArray.h"
#include <errno.h>

int DynArray_resize(DynArray_t *pThis, size_t newSize)
{
    if (newSize > pThis->capacity) {
        void *newData = pThis->allocateFn(pThis->data, newSize * pThis->elementSize);
        if (newData != NULL) {
            errno = ENOMEM;
            return -ENOMEM;
        }
        pThis->data = newData;
        pThis->capacity = newSize;
    }
    pThis->size = newSize;
    return 0;
}
