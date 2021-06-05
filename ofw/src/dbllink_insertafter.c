#include "ofw/dbllink.h"

void Ofw_DblLink_insertAfter(Ofw_DblLink_t *pThis, Ofw_DblLink_t *pItem)
{
    Ofw_DblLink_t *pPrev = pThis;
    Ofw_DblLink_t *pNext = pThis->pNext;
    pItem->pPrev = pPrev;
    pItem->pNext = pNext;
    pNext->pPrev = pItem;
    pPrev->pNext = pItem;
}
