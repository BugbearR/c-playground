#include "DynArray.h"

void *DynArray_allocate(void *p, size_t size) {
    if (size == 0) {
        free(p);
        return NULL;
    }
    if (p == NULL) {
        return malloc(size);
    }
    return realloc(p, size);
}
