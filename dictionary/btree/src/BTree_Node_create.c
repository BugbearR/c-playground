#include "BTree.h"

#include <stdlib.h>

BTree_Node_t *BTree_Node_create()
{
    BTree_Node_t *pNode;
    pNode = malloc(sizeof(BTree_Node_t));
    if (pNode == NULL)
    {
        return NULL;
    }
    *pNode = (BTree_Node_t){0};
    // pNode->entry[0] = (BTree_Entry_t){0};
    return pNode;
}
