#include "BTree.h"

#include <stdio.h>
#include <assert.h>

void BTree_validate(BTree_t *pTree)
{
    assert(pTree != NULL);
    BTree_Node_validate(pTree->pRoot);
}
