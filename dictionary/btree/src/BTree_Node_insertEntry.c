#include "BTree.h"

#include <stdio.h>
#include <memory.h>

int BTree_Node_insertEntry(BTree_t *pTree, BTree_Node_t *pNode, int index, int32_t value, BTree_Node_t *pChild)
{
    // printf("BTree_Node_insertEntry pNode:%p index:%d, value:%d, pChild:%p\n", pNode, index, value, pChild);
    int subResult;
    int indexWk = index;
    BTree_Node_t *pNodeForIns = pNode;
    // ノードの分割が必要なら
    if (pNode->count == BTREE_NODE_ENTRY_MAX)
    {
        BTree_Node_t *pNewNode = BTree_Node_create();
        if (pNewNode == NULL)
        {
            return -1;
        }

        // 後半を新しいノードにコピーする。
        int cutIndex = BTREE_NODE_ENTRY_MAX / 2;
        int copyCount = BTREE_NODE_ENTRY_MAX - cutIndex - 1; // -1 は上に引き上げる値のため

        // printf("before divide\n");
        // BTree_Node_dump(pTree, pNode, 0, false);

        memcpy(
            pNewNode->entry,
            &(pNode->entry[cutIndex + 1]), // +1 は中央の値の分ずらす
            sizeof(BTree_Entry_t) * (copyCount + 1)); // +1 は再右端のリンクのため
        pNode->count = cutIndex;
        pNewNode->count = copyCount;

        // 新しいノードの子の親をつけなおす。
        int i;
        for (i = 0; i < pNewNode->count + 1; i++)
        {
            BTree_Node_t *pChildWk = pNewNode->entry[i].pChild;
            if (pChildWk != NULL)
            {
                pChildWk->pParent = pNewNode;
            }
        }

        // 中点の値を上のノードに追加する。
        // 挿入場所を確定する
        int32_t upValue = pNode->entry[cutIndex].value;
        // printf("upValue:%d\n", upValue);

        BTree_Node_t *pParent = pNode->pParent;
        // 親ノードがない場合
        if (pParent == NULL)
        {
            // 新しくノードを作ってルートの差し替え
            pParent = BTree_Node_create();
            if (pParent == NULL)
            {
                return -1;
            }
            pTree->pRoot = pParent;

            pParent->entry[0].pChild = pNode;
            pParent->entry[0].value = upValue;
            pParent->entry[1].pChild = pNewNode;

            pNode->pParent = pParent;
            pNewNode->pParent = pParent;
            pParent->count = 1;
        }
        else
        {
            pNewNode->pParent = pParent; // 分割されたら付けなおされるが、呼び出した処理の中から行われる。
            int parentIndex = BTree_Node_findEdge(pNode);
            subResult = BTree_Node_insertEntry(pTree, pParent, parentIndex, upValue, pNewNode);
            if (subResult != 0)
            {
                return -1;
            }
        }

        // 新しいエントリは、分割してから、挿入する
        // コピーが増えてしまうが、ここは簡略化する。
        // cutIndex 以下なら前、cutIndex より大きいなら後になる。
        if (cutIndex < indexWk)
        {
            indexWk -= cutIndex + 1;
            pNodeForIns = pNewNode;
        }
    }

    // 値と枝を挿入する
    // printf("indexWk:%d, value:%d\n", indexWk, value);

    // printf("before insert\n");
    // BTree_Node_dump(pTree, pNodeForIns, 0, true);

    BTree_Entry_t *pEntry = &(pNodeForIns->entry[indexWk]);
    BTree_Entry_t *pNextEntry = pEntry + 1;
    // BTree_Node_t *pOrgChild = pNextEntry->pChild;
    int moveCount = pNodeForIns->count - indexWk + 1; // + 1 は終端用
    if (moveCount > 0)
    {
        memmove(
            pNextEntry,
            pEntry,
            sizeof(BTree_Entry_t) * moveCount
        );
    }
    // pEntry->pChild = pOrgChild;
    pEntry->value = value;
    pNextEntry->pChild = pChild;
    if (pChild != NULL)
    {
        pChild->pParent = pNodeForIns;
    }
    pNodeForIns->count++;

    // printf("after insert\n");
    // BTree_Node_dump(pTree, pNodeForIns, 0, true);

    return 0;
}
