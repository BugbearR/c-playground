#include "BTree.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include <stdio.h>

int BTree_Node_merge(BTree_t *pTree, BTree_Node_t *pNode)
{
    // printf("BTree_Node_merge pNode:%p\n", pNode);
    if (pNode->pParent == NULL)
    {
        if (pNode->count == 0)
        {
            BTree_Node_t *pChild = pNode->entry[0].pChild;
            // XXX 気になるなら中のデータをクリアしてから
            // pNode->entry[0].pChild = NULL;
            BTree_Node_destroy(pNode);
            pTree->pRoot = pChild;
            if (pChild != NULL)
            {
                pChild->pParent = NULL;
            }
        }
        return 0;
    }

    int index = BTree_Node_findEdge(pNode);
    BTree_Node_t *pParent = pNode->pParent;
    // printf("found index:%d\n", index);

    // 左
    BTree_Node_t *pLeftNode = NULL;
    BTree_Node_t *pLeftParentNode = NULL;
    if (index > 0)
    {
        pLeftNode = pParent->entry[index - 1].pChild;
    }
    // 右
    BTree_Node_t *pRightNode = NULL;
    if (index < pParent->count)
    {
        pRightNode = pParent->entry[index + 1].pChild;
    }

    bool isTargetLeft = false;
    if (pLeftNode == NULL)
    {
        isTargetLeft = false;
    }
    else if (pRightNode == NULL)
    {
        isTargetLeft = true;
    }
    else
    {
        isTargetLeft = (pRightNode->count < pLeftNode->count);
    }

    // printf("isTargetLeft:%d\n", isTargetLeft);

    BTree_Entry_t *pParentMidEntry;
    int midIndex;
    BTree_Node_t *pNode0;
    BTree_Node_t *pNode1;
    if (isTargetLeft)
    {
        midIndex = index - 1;
        pNode0 = pLeftNode;
        pNode1 = pNode;
    }
    else
    {
        midIndex = index;
        pNode0 = pNode;
        pNode1 = pRightNode;
    }

    if (pNode0->count + pNode1->count + 1 <= BTREE_NODE_ENTRY_MAX)
    {
        // printf("merge 0, 1\n");
        // マージ
        memcpy(
            &(pNode0->entry[pNode0->count + 1]),
            &(pNode1->entry[0]),
            sizeof(BTree_Entry_t) * (pNode1->count + 1)
        );
        // printf("pParent:%p\n", pParent);
        // BTree_Node_dump(pTree, pParent, 0, false);
        // printf("pNode0:%p\n", pNode0);
        // BTree_Node_dump(pTree, pNode0, 0, false);
        // printf("pNode1:%p\n", pNode1);
        // BTree_Node_dump(pTree, pNode1, 0, false);

        pNode0->entry[pNode0->count].value = pParent->entry[midIndex].value;
        int i;
        if (pNode1->entry[0].pChild != NULL)
        {
            for (i = 0; i <= pNode1->count; i++)
            {
                pNode1->entry[i].pChild->pParent = pNode0;
            }
        }
        // printf("pNode:%p pParent:%p\n", pNode0, pParent);
        BTree_Node_deleteEntry(pParent, midIndex);
        pParent->entry[midIndex].pChild = pNode0;
        pNode0->count += pNode1->count + 1;
        // printf("after pNode0:%p pParent:%p\n", pNode0, pNode0->pParent);
        // BTree_Node_dump(pTree, pNode0, 0, false);
        // printf("after pParent:%p pParent->pParent:%p\n", pParent, pParent->pParent);
        // BTree_Node_dump(pTree, pParent, 0, false);

        // XXX 気になるなら中のデータをクリアしてから
        BTree_Node_destroy(pNode1);
        if (pParent->count < BTREE_NODE_ENTRY_MAX / 2)
        {
            return BTree_Node_merge(pTree, pParent);
        }
        return 0;
    }

    if (pNode0->count < pNode1->count)
    {
        // 右(1)から左(0)にローテート
        // printf("rotate 1to0\n");
        pNode0->entry[pNode0->count].value = pParent->entry[midIndex].value;
        pParent->entry[midIndex].value = pNode1->entry[0].value;
        pNode0->entry[pNode0->count + 1].pChild = pNode1->entry[0].pChild;
        if (pNode1->entry[0].pChild != NULL)
        {
            pNode0->entry[pNode0->count + 1].pChild->pParent = pNode0;
        }
        memmove(
            &(pNode1->entry[0]),
            &(pNode1->entry[1]),
            sizeof(BTree_Entry_t) * pNode1->count
        );
        pNode0->count++;
        pNode1->count--;
    }
    else
    {
        // 左(0)から右(1)にローテート
        // printf("rotate 0to1\n");
        // printf("pParent:%p\n", pParent);
        // BTree_Node_dump(pTree, pParent, 0, false);
        // printf("pNode0:%p\n", pNode0);
        // BTree_Node_dump(pTree, pNode0, 0, false);
        // printf("pNode1:%p\n", pNode1);
        // BTree_Node_dump(pTree, pNode1, 0, false);

        memmove(
            &(pNode1->entry[1]),
            &(pNode1->entry[0]),
            sizeof(BTree_Entry_t) * (pNode1->count + 1)
        );
        pNode1->entry[0].value = pParent->entry[midIndex].value;
        pParent->entry[midIndex].value = pNode0->entry[pNode0->count - 1].value;
        pNode1->entry[0].pChild = pNode0->entry[pNode0->count].pChild;
        if (pNode1->entry[0].pChild != NULL) {
            pNode1->entry[0].pChild->pParent = pNode1;
        }
        pNode1->count++;
        pNode0->count--;

        // printf("after pParent:%p\n", pParent);
        // BTree_Node_dump(pTree, pParent, 0, false);
        // printf("after pNode0:%p\n", pNode0);
        // BTree_Node_dump(pTree, pNode0, 0, false);
        // printf("after pNode1:%p\n", pNode1);
        // BTree_Node_dump(pTree, pNode1, 0, false);
    }
    return 0;
}
