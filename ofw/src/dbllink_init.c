#include "ofw/dbllink.h"

void Ofw_DblLink_init(Ofw_DblLink_t *pThis, Ofw_DblLink_t *pNext, Ofw_DblLink_t *pPrev)
{
    pThis->pNext = pNext;
    pThis->pPrev = pPrev;
}
