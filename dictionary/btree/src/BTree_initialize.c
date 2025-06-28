#include "BTree.h"

void BTree_initialize(BTree_t *pThis)
{
    pThis->count = 0;
    pThis->pRoot = NULL;
}
