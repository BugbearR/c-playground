#include "ofw/deque.h"

void Ofw_Deque_init(Ofw_Deque_t *pThis)
{
    pThis->length = 0;
    Ofw_DequeItem_init(&(pThis->root), &(pThis->root), &(pThis->root), NULL);
}
