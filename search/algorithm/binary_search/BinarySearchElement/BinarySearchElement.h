#ifndef BINARYSEARCHELEMENT_H_
#define BINARYSEARCHELEMENT_H_

int BinarySearchElement_search(
    void *pObj,
    int count,
    int (*fnCompare)(void *pObj, int idx)
);

#endif // BINARYSEARCHELEMENT_H_
