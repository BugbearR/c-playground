#ifndef BINARYSEARCH_H_
#define BINARYSEARCH_H_

int BinarySearch_search(
    void *pObj,
    int count,
    int (*fnCompare)(void *pObj, int idx)
);

int BinarySearch_searchMemory(
    const void *p,
    int size,
    int count,
    const void *pKey,
    int keySize,
    int (*fnCompare)(const void *p, void *pKey, void *pContext),
    void *pContext
);

#endif // BINARYSEARCH_H_
