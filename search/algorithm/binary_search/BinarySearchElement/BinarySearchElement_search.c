#include "BinarySearchElement.h"

#include <stdio.h>

int BinarySearchElement_search(
    void *pObj,
    int count,
    int (*fnCompare)(void *pObj, int idx)
)
{
    int lo = 0;
    int hi = count - 1;
    int mid;
    int tryCount = 0;

    while (hi >= lo) {
        mid = lo + (hi - lo) / 2;
        tryCount++;
        printf("try: %d, lo: %d, hi: %d, mid: %d\n", tryCount, lo, hi, mid);
        int cmp = fnCompare(pObj, mid);
        if (cmp > 0) {
            hi = mid - 1;
        } else if (cmp < 0) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }

    return -(lo + 1); // Not found
}
