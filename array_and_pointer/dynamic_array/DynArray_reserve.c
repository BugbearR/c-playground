#include "DynArray.h"
#include <errno.h>

int DynArray_reserve(DynArray_t *pThis, size_t newCapacity)
{
    if (newCapacity > pThis->capacity) {
        void *newData = pThis->allocateFn(pThis->data, newCapacity * pThis->elementSize);
        if (newData) {
            pThis->data = newData;
            pThis->capacity = newCapacity;
        } else {
            errno = ENOMEM;
            return -ENOMEM;
        }
    }
}
