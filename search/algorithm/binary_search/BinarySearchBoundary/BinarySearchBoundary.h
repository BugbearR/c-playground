#ifndef BINARYSEARCHBOUNDARY_H_
#define BINARYSEARCHBOUNDARY_H_

#include <stdbool.h>

int BinarySearchBoundary_search(
    void *pObj,
    int ok,
    int ng,
    bool (*fnIsOk)(void *pObj, int idx)
);

#endif // BINARYSEARCHBOUNDARY_H_
