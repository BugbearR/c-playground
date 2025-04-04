#ifndef QUICKSORT_H_
#define QUICKSORT_H_

typedef struct QuickSort_Ctx {
    void *pObj; // Pointer to the object to be sorted
    int (*fnCompare)(void *pObj, int idx1, int idx2); // Comparison function
    void (*fnSwap)(void *pObj, int idx1, int idx2); // Swap function
} QuickSort_Ctx_t;

int QuickSort_sort(
    void *pObj,
    int count,
    int (*fnCompare)(void *pObj, int idx1, int idx2),
    void (*fnSwap)(void *pObj, int idx1, int idx2)
);

int QuickSort_sortMemory(
    const void *p,
    int size,
    int count,
    int (*fnCompare)(const void *p1, const void *p2, void *pContext),
    void *pContext
);

#endif // QUICKSORT_H_
