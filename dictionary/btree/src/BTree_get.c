#include "BTree.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

BTree_get_result_t BTree_get(BTree_t *pTree, int32_t value)
{
    BTree_Node_t *pNode = pTree->pRoot;
    int index;

    if (pNode == NULL)
    {
        return (BTree_get_result_t) {
            .found = false
        };
    }

    BTree_Position_t r = BTree_Node_findEntry(pNode, value, true);
    return (BTree_get_result_t) {
        .found = (r.index >= 0),
        .value = ((r.index >= 0) ? r.pNode->entry[r.index].value : 0)
    };
}
