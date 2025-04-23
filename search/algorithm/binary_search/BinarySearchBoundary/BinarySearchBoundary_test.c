#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "BinarySearchBoundary.h"

typedef struct Target {
    int n;
} Target_t;

bool isOk(void *pObj, int idx) {
    Target_t *pTarget = (Target_t *)pObj;

    return idx <= pTarget->n;
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("usage: %s targetNumber ok ng\n", argv[0]);
        return EXIT_FAILURE;
    }

    int targetN = atoi(argv[1]);
    int ok = atoi(argv[2]);
    int ng = atoi(argv[3]);

    Target_t target;
    target.n = targetN;

    int okBound = BinarySearchBoundary_search(&target, ok, ng, isOk);
    printf("result ok: %d\n", okBound);

    return EXIT_SUCCESS;
}
