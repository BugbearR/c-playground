#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BinarySearchRange.h"

typedef struct Target {
    int n;
} Target_t;

bool isTargetInRange(void *pObj, int lo, int hi) {
    Target_t *pTarget = (Target_t *)pObj;

    return (lo <= pTarget->n && pTarget->n < hi);
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("usage: %s targetNumber lo hi minD\n", argv[0]);
        return EXIT_FAILURE;
    }

    int targetN = atoi(argv[1]);
    int lo = atoi(argv[2]);
    int hi = atoi(argv[3]);
    int minD = atoi(argv[4]);

    Target_t target;
    target.n = targetN;

    int resLo;
    int resHi;

    bool isInRange = BinarySearchRange_search(&target, lo, hi, minD, &resLo, &resHi, isTargetInRange);
    if (isInRange) {
        printf("result lo: %d, hi: %d\n", resLo, resHi);
    }
    else {
        printf("target is not in range.\n");
    }

    return EXIT_SUCCESS;
}
