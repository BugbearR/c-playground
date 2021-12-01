#include <stdio.h>
#include <stdlib.h>

#define DATA_COUNT (100)

int mycompare(const void *p1, const void *p2, void *pInfo)
{
    int d1 = *(int *)p1;
    int d2 = *(int *)p2;
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;
    return 0;
}

#define ofw_Array_getPtrM(pBase, sz, n) \
    ((void *)(((char *)pBase) + (sz) * (n)))

char *partition(char *pBase, size_t sz, int n, int(*compareFn)(const void *p1, const void *p2, void *pInfo), void *pInfo)
{
    char *pLo = pBase;
    char *pHi = ofw_Array_getPtrM(pBase, sz, n - 1);
    char *pMid = ofw_Array_getPtrM(pBase, sz, n / 2);

    if (compareFn(pLo, pMid, pInfo) > 0)
    {
        swap(pLo, pMid, sz);
    }
    if (compareFn(pMid, pHi, pInfo) > 0)
    {
        swap(pLo, pMid, sz);
        if (compareFn(pLo, pMid, pInfo) > 0)
        {
            swap(pLo, pMid, sz);
        }
    }

    while (1)
    {
        while (compareFn(pLo, pMid, pInfo) < 0)
        {
            pLo += sz;
        }

        while (compareFn(pMid, pHi, pInfo) < 0)
        {
            pHi -= sz;
        }
        if (pLo >= pHi)
        {
            return pHi + sz;
        }

        swap(pLo, pHi, sz);

        if (pLo == pMid)
        {
            pMid = pHi;
        }
        else if (pHi == pMid)
        {
            pMid = pLo;
        }
        pLo += sz;
        pHi -= sz;
    }
}

void quickSort(void *pBase, size_t sz, int n, int(*compareFn)(const void *p1, const void *p2, void *pInfo), void *pInfo)
{
    char *p = partition(pBase, sz, n, compareFn, pInfo);
    char *nLo = (p - (char *)pBase) / sz;
    char *nNi = ((char *)ofw_Array_getPtrM(pBase, sz, n) - p) / sz;
    quickSort(pBase, sz, n, compareFn, pInfo);
    quickSort(p, sz, n, compareFn, pInfo);
}

int main(int argc, char *argv[])
{
    unsigned int seed;
    int i;
    int d[DATA_COUNT];

    if (argc >= 2)
    {
        sscanf(argv[1], "%u", &seed);
        srand(seed);
    }

    for (i = 0; i < DATA_COUNT; i++)
    {
        d[i] = rand();
    }

    qsort(d, DATA_COUNT, sizeof(int), mycompare);

    for (i = 0; i < DATA_COUNT; i++)
    {
        printf("%d\n", d[i]);
    }

    return EXIT_SUCCESS;
}
