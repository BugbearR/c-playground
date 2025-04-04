#include "FixArray.h"

#include <errno.h>

void *FixArray_at(FixArray_t *pThis, size_t index)
{
    if (pThis == NULL || index >= pThis->size) {
        errno = EINVAL;
        return NULL;
    }

    return ((char *)pThis->pArray) + (index * pThis->elementSize);
}
