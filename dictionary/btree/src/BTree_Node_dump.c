#include "BTree.h"

#include <stdio.h>
#include <assert.h>

static void indentLevel(int level)
{
    int i;
    for (i = 0; i < level * 4; i++)
    {
        printf(" ");
    }
}

void BTree_Node_dump(BTree_t *pTree, BTree_Node_t *pNode, int level, bool recursive)
{
    int i;

    assert(level < 6);
    indentLevel(level);
    printf("pNode: %p pParent:%p\n", pNode, pNode->pParent);
    if (pNode == NULL)
    {
        return;
    }
    for (i = 0; i <= pNode->count; i++)
    {
        BTree_Node_t *pChild = pNode->entry[i].pChild;
        indentLevel(level);
        printf("%d:pChild: %p\n", i, pChild);

        if (recursive && pChild != NULL)
        {
            BTree_Node_dump(pTree, pChild, level + 1, true);
        }

        if (i < pNode->count) {
            indentLevel(level);
            printf("%d:value: %d\n", i, pNode->entry[i].value);
        }
    }
}
