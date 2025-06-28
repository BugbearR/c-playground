#include "BTree.h"

#include <stdlib.h>

void BTree_Node_finalize(BTree_Node_t *pNode)
{
    if (pNode == NULL)
    {
        return;
    }

    int i;
    for (i = 0; i < pNode->count; i++)
    {
        BTree_Node_finalize(pNode->entry[i].pChild);
        // XXX 気になるならポインタを消す
        // pNode->entry[i].pChild = NULL;
    }
    // XXX 気になるならカウンタを0にする
    // pNode->count = 0;

    BTree_Node_destroy(pNode);
}
