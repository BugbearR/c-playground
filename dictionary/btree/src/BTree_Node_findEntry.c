#include "BTree.h"

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

BTree_Position_t BTree_Node_findEntry(BTree_Node_t *pNode, int32_t value, bool recursive)
{
    // printf("BTree_Node_findEntry pNode:%p value:%" PRId32 "\n", pNode, value);
    if (pNode->count == 0)
    {
        return (BTree_Position_t) {
            .pNode = pNode,
            .index = -1
        };
    }

    assert(pNode->count <= BTREE_NODE_ENTRY_MAX);

    for (;;) {
        int i;

        // binary search
        int s = 0;
        int e = pNode->count;
        int m;
        int childOffset;
        BTree_Entry_t *pEntry;
        while (s < e)
        {
            assert(s >= 0);
            assert(e >= 0);
            m = (s + e) / 2;
            pEntry = &(pNode->entry[m]);
            int entryValue = pEntry->value;
            if (pEntry->value < value)
            {
                s = m + 1;
                childOffset = 1;
            }
            else if (value < pEntry->value)
            {
                e = m;
                childOffset = 0;
            }
            else
            {
                return (BTree_Position_t) {
                    .pNode = pNode,
                    .index = m
                };
            }
        }

        BTree_Node_t *pChild;
        if (!recursive || (pChild = (pEntry + childOffset)->pChild) == NULL)
        {
            return (BTree_Position_t) {
                .pNode = pNode,
                .index = -(m + childOffset + 1)
            };
        }
        pNode = pChild;
    }
}
