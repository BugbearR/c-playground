#include "QuickSort.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct QuickSort_Memory {
    const char *p;
    int size;
    int count;
} QuickSort_Memory_t;

static int compareMemory(void *pObj, int idx1, int idx2)
{
    QuickSort_Memory_t *pCtx = (QuickSort_Memory_t *)pObj;
    const char *p1 = pCtx->p + (idx1 * pCtx->size);
    const char *p2 = pCtx->p + (idx2 * pCtx->size);
    return memcmp(p1, p2, pCtx->size);
}

static int swapMemory(void *pObj, int idx1, int idx2)
{
    QuickSort_Memory_t *pCtx = (QuickSort_Memory_t *)pObj;
    char *p1 = (char *)(pCtx->p + (idx1 * pCtx->size));
    char *p2 = (char *)(pCtx->p + (idx2 * pCtx->size));
    size_t size = pCtx->size;
    size_t i;
    char buf[4096];

    i = 0;
    while (i < size) {
        if (i + sizeof(buf) < size) {
            memcpy(buf, p1, sizeof(buf));
            memcpy(p1, p2, sizeof(buf));
            memcpy(p2, buf, sizeof(buf));
            p1 += sizeof(buf);
            p2 += sizeof(buf);
            i += sizeof(buf);
        } else {
            memcpy(buf, p1, size - i);
            memcpy(p1, p2, size - i);
            memcpy(p2, buf, size - i);
            break; // i = size;
        }
    }

    return 0;
}

int QuickSort_sortMemory(const void *p, int size, int count,
    int (*fnCompare)(const void *p1, const void *p2, void *pContext), void *pContext)
{
    QuickSort_Memory_t ctx =
    {
        .p = (const char *)p,
        .size = size,
        .count = count
    };
    return QuickSort_sort(&ctx, count, compareMemory, swapMemory);
}
