#include "DynArray.h"
#include <errno.h>

void *DynArray_at(DynArray_t *pThis, size_t index)
{
    if (pThis == NULL || index >= pThis->size) {
        errno = EINVAL;
        return NULL;
    }

    return (char *)pThis->data + (index * pThis->elementSize);
}
