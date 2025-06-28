#include "BTree.h"

void BTree_finalize(BTree_t *pThis)
{
    if (pThis == NULL)
    {
        return;
    }

    BTree_Node_finalize(pThis->pRoot);
}
