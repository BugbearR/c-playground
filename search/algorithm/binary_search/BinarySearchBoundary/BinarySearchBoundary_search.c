#include "BinarySearchBoundary.h"

#include <stdio.h>

int BinarySearchBoundary_search(
    void *pObj,
    int ok,
    int ng,
    bool (*fnIsOk)(void *pObj, int idx)
)
{
    int okWk = ok;
    int ngWk = ng;
    int mid;
    int count = 0;

    while (((okWk < ngWk) ? (ngWk - okWk) : (okWk - ngWk)) > 1) { // abs(okWk - ngWk) > 1
        mid = (okWk + ngWk) / 2;
        count++;
        printf("try: %d, ok: %d, ng: %d, mid: %d\n", count, okWk, ngWk, mid);
        if (fnIsOk(pObj, mid)) {
            okWk = mid;
        }
        else {
            ngWk = mid;
        }
    }

    return okWk;
}
