#include "BTree.h"

#include <inttypes.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

void BTree_Node_deleteEntry(BTree_Node_t *pNode, int index)
{
    // printf("BTree_deleteEntry Node:%p index:%d (value:%d)\n", pNode, index, pNode->entry[index].value);
    assert(index >= 0);
    assert(index < pNode->count);

    BTree_Entry_t *pEntry = &(pNode->entry[index]);
    BTree_Entry_t *pNextEntry = pEntry + 1;
    // BTree_Node_t *pOrgChild = pNextEntry->pChild;
    int moveCount = pNode->count - index;
    if (moveCount > 0)
    {
        memmove(
            pEntry,
            pNextEntry,
            sizeof(BTree_Entry_t) * moveCount
        );
    }
    pNode->count--;
}
