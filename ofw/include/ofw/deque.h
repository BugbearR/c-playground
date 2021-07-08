#if !defined Ofw_Deque_H_
#define Ofw_Deque_H_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

#include <stdint.h>

typedef struct Ofw_DequeItem_tag
{
    struct Ofw_DequeItem_tag *pNext;
    struct Ofw_DequeItem_tag *pPrev;
    void *pValue;
} Ofw_DequeItem_t;


typedef struct Ofw_Deque_tag
{
    int32_t length;
    Ofw_DequeItem_t root;
} Ofw_Deque_t;

void Ofw_DequeItem_init(Ofw_DequeItem_t *pThis, Ofw_DequeItem_t *pNext, Ofw_DequeItem_t *pPrev, void *pValue);

void Ofw_Deque_init(Ofw_Deque_t *pThis);

#endif /* Ofw_Deque_H_ */
