#include "BTree.h"

#include <stdio.h>

void BTree_dump(BTree_t *pTree)
{
    if (pTree->pRoot == NULL)
    {
        printf("pRoot: NULL\n");
    }
    else
    {
        BTree_Node_dump(pTree, pTree->pRoot, 0, true);
    }
}
