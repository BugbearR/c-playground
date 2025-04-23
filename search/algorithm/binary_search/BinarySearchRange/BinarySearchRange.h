#ifndef BINARYSEARCHRANGE_H_
#define BINARYSEARCHRANGE_H_

#include <stdbool.h>

bool BinarySearchRange_search(
    void *pObj,
    int lo,
    int hi,
    int minD,
    int *pOutLo,
    int *pOutHi,
    bool (*fnIsTargetInRange)(void *pObj, int lo, int hi)
);

#endif // BINARYSEARCH_H_
