#include "BinarySearch.h"

#include <stdio.h>

int BinarySearch_search(
    void *pObj,
    int count,
    int (*fnCompare)(void *pObj, int idx)
)
{
    int lo = 0;
    int hi = count - 1;
    int mid;

    while (hi >= lo) {
        mid = lo + (hi - lo) / 2;
        printf("lo: %d, hi: %d, mid: %d\n", lo, hi, mid);
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
