#include "DynArray.h"
#include <errno.h>
#include <stdlib.h>

DynArray_t *DynArrray_initialize(
    DynArray_t *pThis,
    size_t elementSize,
    size_t initialCapacity,
    void *(*allocateFn)(void *p, size_t))
{
    if (!pThis) {
        errno = EINVAL;
        return NULL;
    }
    if (elementSize == 0) {
        errno = EINVAL;
        return NULL;
    }

    if (allocateFn == NULL) {
        allocateFn = DynArray_allocate;
    }

    if (initialCapacity == 0) {
        initialCapacity = 1;
    }

    pThis->data = allocateFn(NULL, initialCapacity * elementSize);
    if (pThis->data == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    pThis->size = 0;
    pThis->capacity = initialCapacity;
    pThis->elementSize = elementSize;
    pThis->allocateFn = allocateFn;

    return pThis;
}
