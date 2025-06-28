#include "BTree.h"

#include <stdio.h>
#include <assert.h>

void BTree_Node_validate(BTree_Node_t *pNode)
{
    int i;
    int j;

    assert(pNode->count >= 1);
    assert(pNode->count <= BTREE_NODE_ENTRY_MAX);

    int32_t prevValue;
    for (i = 1; i < pNode->count; i++)
    {
        assert(pNode->entry[i-1].value < pNode->entry[i].value);
    }

    if (pNode->entry[0].pChild == NULL)
    {
        for (i = 0; i < pNode->count + 1; i++)
        {
            assert(pNode->entry[i].pChild == NULL);
        }
    }
    else
    {
        BTree_Node_t *pChild = pNode->entry[0].pChild;
        int32_t lo;
        int32_t hi = pNode->entry[0].value;
        for (j = 0; j < pChild->count; j++)
        {
            assert(pChild->entry[j].value < hi);
        }

        for (i = 0; i < pNode->count - 1; i++)
        {
            pChild = pNode->entry[i+1].pChild;
            int32_t lo = pNode->entry[i].value;
            int32_t hi = pNode->entry[i+1].value;
            for (j = 0; j < pChild->count; j++)
            {
                assert(pChild->entry[j].value > lo);
                assert(pChild->entry[j].value < hi);
            }
        }
        pChild = pNode->entry[pNode->count].pChild;
        lo = pNode->entry[pNode->count - 1].value;
        for (j = 0; j < pChild->count; j++)
        {
            assert(pChild->entry[j].value > lo);
        }

        for (i = 0; i < pNode->count + 1; i++)
        {
            pChild = pNode->entry[i].pChild;
            // if (pNode != pChild->pParent) {
            //     printf("pNode:%p pChild:%p pChild->pParent:%p\n", pNode, pChild, pChild->pParent);
            // }
            assert(pNode == pChild->pParent);
            BTree_Node_validate(pChild);
        }
    }
}
