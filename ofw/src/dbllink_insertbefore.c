#include "ofw/dbllink.h"

void Ofw_DblLink_insertBefore(Ofw_DblLink_t *pThis, Ofw_DblLink_t *pItem)
{
    Ofw_DblLink_t *pPrev = pThis->pPrev;
    Ofw_DblLink_t *pNext = pThis;
    pItem->pPrev = pPrev;
    pItem->pNext = pNext;
    pNext->pPrev = pItem;
    pPrev->pNext = pItem;
}
