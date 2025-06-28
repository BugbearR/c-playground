#include "BTree.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

int BTree_add(BTree_t *pTree, int32_t value)
{
    BTree_Node_t *pNode = pTree->pRoot;
    int index;

    if (pNode == NULL)
    {
        pNode = BTree_Node_create();
        if (pNode == NULL)
        {
            return -1;
        }
        pTree->pRoot = pNode;
        index = 0;
    }
    else
    {
        BTree_Position_t r = BTree_Node_findEntry(pNode, value, true);
        if (r.index >= 0)
        {
            // 既に追加済み
            errno = EEXIST;
            return -1;
        }

        // 挿入位置に変換する
        index = -(r.index + 1);
        pNode = r.pNode;
    }

    int subResult = BTree_Node_insertEntry(pTree, pNode, index, value, NULL);
    if (subResult != 0)
    {
        int myErrno = errno;
        fprintf(stderr, "BTree_Node_insertEntry error. errno:%d message:%s", myErrno, strerror(errno));
        return -1;
    }

    pTree->count++;

    return 0;
}
