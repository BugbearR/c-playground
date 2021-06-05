#include "ofw/deque.h"

void Ofw_DequeItem_init(Ofw_DequeItem_t *pThis, Ofw_DequeItem_t *pNext, Ofw_DequeItem_t *pPrev, void *pValue)
{
    pThis->pNext = pNext;
    pThis->pPrev = pPrev;
    pThis->pValue = pValue;
}
