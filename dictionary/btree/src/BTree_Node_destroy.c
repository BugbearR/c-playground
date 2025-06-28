#include "BTree.h"

#include <stdlib.h>

void BTree_Node_destroy(BTree_Node_t *pNode)
{
    free(pNode);
}
