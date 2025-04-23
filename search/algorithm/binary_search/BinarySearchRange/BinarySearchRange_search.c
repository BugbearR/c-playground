#include "BinarySearchRange.h"

#include <stdio.h>

bool BinarySearchRange_search(
    void *pObj,
    int lo,
    int hi,
    int minD,
    int *pOutLo,
    int *pOutHi,
    bool (*fnIsTargetInRange)(void *pObj, int lo, int hi)
)
{
    int loWk = lo;
    int hiWk = hi;
    int mid;
    int count = 0;

    if (!fnIsTargetInRange(pObj, lo, hi)) {
        return false;
    }

    while (hiWk - loWk > minD) {
        mid = loWk + (hiWk - loWk) / 2;
        count++;
        printf("try: %d, lo: %d, hi: %d, mid: %d\n", count, loWk, hiWk, mid);
        if (fnIsTargetInRange(pObj, loWk, mid)) {
            hiWk = mid;
        }
        else {
            loWk = mid;
        }
    }

    *pOutLo = loWk;
    *pOutHi = hiWk;

    return true;
}
