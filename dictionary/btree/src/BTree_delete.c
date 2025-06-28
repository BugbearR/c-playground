#include "BTree.h"

#include <errno.h>
#include <inttypes.h>

int BTree_delete(BTree_t *pTree, int32_t value)
{
    int subResult;
    // printf("BTree_delete %" PRId32 "\n", value);
    if (pTree->pRoot == NULL)
    {
        errno = ENOENT;
        return -1;
    }

    BTree_Position_t res = BTree_Node_findEntry(pTree->pRoot, value, true);
    if (res.index < 0)
    {
        errno = ENOENT;
        return -1;
    }

    // 左右の子のどちらかから引き抜く
    int index = res.index;
    BTree_Node_t *pLeftChild = res.pNode->entry[index].pChild;
    // 子がいないなら見つけたページから引き抜く
    if (pLeftChild == NULL)
    {
        BTree_Node_deleteEntry(res.pNode, res.index);
        // 数が少なくなったらマージする。
        if (res.pNode->count < BTREE_NODE_ENTRY_MAX / 2)
        {
            int subResult;
            subResult = BTree_Node_merge(pTree, res.pNode);
            if (subResult != 0)
            {
                return -1;
            }
        }

        pTree->count--;
        return 0;
    }

    int leftDepth = 0;
    // 左の右端を検索する。
    BTree_Node_t *pNextChild;
    if (pLeftChild != NULL)
    {
        for (;;)
        {
            pNextChild = pLeftChild->entry[pLeftChild->count].pChild;
            if (pNextChild == NULL)
            {
                break;
            }
            pLeftChild = pNextChild;
            leftDepth++;
        }
    }

    // 右の左端を検索する。
    int rightDepth = 0;
    BTree_Node_t *pRightChild = res.pNode->entry[index + 1].pChild;
    if (pRightChild != NULL)
    {
        for (;;)
        {
            pNextChild = pRightChild->entry[0].pChild;
            if (pNextChild == NULL)
            {
                break;
            }
            pRightChild = pNextChild;
            rightDepth++;
        }
    }

    // 両方ある場合は、どちらか深い方、同じ深さなら多い方から値を抜き取る。
    bool isTargetLeft;
    do
    {
        if (pLeftChild == NULL)
        {
            isTargetLeft = false;
            break;
        }

        if (pRightChild == NULL)
        {
            isTargetLeft = true;
            break;
        }

        if (leftDepth < rightDepth)
        {
            isTargetLeft = false;
            break;
        }

        if (leftDepth > rightDepth)
        {
            isTargetLeft = true;
            break;
        }

        if (pLeftChild->count <= pRightChild->count)
        {
            isTargetLeft = false;
            break;
        }

        isTargetLeft = true;
    } while (false);

    if (isTargetLeft)
    {
        res.pNode->entry[index].value = pLeftChild->entry[pLeftChild->count - 1].value;
        BTree_Node_deleteEntry(pLeftChild, pLeftChild->count - 1);
        if (pLeftChild->count < BTREE_NODE_ENTRY_MAX / 2)
        {
            BTree_Node_merge(pTree, pLeftChild);
        }
    }
    else
    {
        res.pNode->entry[index].value = pRightChild->entry[0].value;
        BTree_Node_deleteEntry(pRightChild, 0);
        if (pRightChild->count < BTREE_NODE_ENTRY_MAX / 2)
        {
            BTree_Node_merge(pTree, pRightChild);
        }
    }
    pTree->count--;
    return 0;
}
