#include "DynArray.h"
#include <errno.h>

ssize_t DynArray_capacity(DynArray_t *pThis)
{
    if (pThis == NULL) {
        errno = EINVAL;
        return -1;
    }
    return pThis->capacity;
}
