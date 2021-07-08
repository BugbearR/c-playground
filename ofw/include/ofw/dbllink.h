#if !defined Ofw_DblLink_H_
#define Ofw_DblLink_H_ 1

#ifdef HAVE_PRAGMA_ONCE
#pragma once
#endif

typedef struct Ofw_DblLink_tag
{
    struct Ofw_DblLink_tag *pNext;
    struct Ofw_DblLink_tag *pPrev;
} Ofw_DblLink_t;

void Ofw_DblLink_init(Ofw_DblLink_t *pThis, Ofw_DblLink_t *pNext, Ofw_DblLink_t *pPrev);

void Ofw_DblLink_insertBefore(Ofw_DblLink_t *pThis, Ofw_DblLink_t *pItem);

void Ofw_DblLink_insertAfter(Ofw_DblLink_t *pThis, Ofw_DblLink_t *pItem);

void Ofw_DblLink_remove(Ofw_DblLink_t *pThis);

#endif /* Ofw_DblLink_H_ */
