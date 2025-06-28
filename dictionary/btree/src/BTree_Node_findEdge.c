#include "BTree.h"

int BTree_Node_findEdge(BTree_Node_t *pNode)
{
    int i;
    BTree_Node_t *pParent = pNode->pParent;
    for (i = 0; i < pParent->count + 1; i++)
    {
        if (pParent->entry[i].pChild == pNode)
        {
            return i;
        }
    }
    return -1;
}
