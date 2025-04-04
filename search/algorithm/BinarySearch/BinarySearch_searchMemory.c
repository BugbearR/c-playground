#include "BinarySearch.h"

typedef struct BinarySearch_Memory {
    const char *p;
    int size;
    int count;
    const char *pKey;
    int keySize;
} BinarySearch_Memory_t;

static int BinarySearch_compareMemory(
    void *pObj,
    int idx
)
{
    BinarySearch_Memory_t *pCtx = (BinarySearch_Memory_t *)pObj;
    const char *p1 = pCtx->p + (idx * pCtx->size);
    return memcmp(p1, pCtx->pKey, pCtx->keySize);
}

int BinarySearch_searchMemory(
    const void *p,
    int size,
    int count,
    const void *pKey,
    int keySize,
    int (*fnCompare)(const void *p, void *pKey, void *pContext),
    void *pContext
)
{
    BinarySearch_Memory_t ctx = {
        .p = (const char *)p,
        .size = size,
        .count = count,
        .pKey = (const char *)pKey,
        .keySize = keySize
    };

    return BinarySearch_search(&ctx, count, BinarySearch_compareMemory);
}
