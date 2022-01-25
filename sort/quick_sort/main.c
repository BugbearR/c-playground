#include <stdio.h>
#include <stdlib.h>

#define DATA_COUNT (100)

int mycompare(void *pObj, int idx1, int idx2)
{
    int *p = pObj;

    int d1 = p[idx1];
    int d2 = p[idx2];
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;
    return 0;
}

void myswap(void *pObj, int idx1, int idx2)
{
    int *p = pObj;

    int tmp = p[idx1];
    p[idx1] = p[idx2];
    p[idx2] = tmp;
}

int partition(void *pObj, int fromIdx, int toIdx,
    int (*compareFn)(void *pObj, int idx1, int idx2),
    void (*swapFn)(void *pObj, int idx1, int idx2))
{
    if (toIdx - fromIdx <= 1) {
        return fromIdx + 1;
    }

    int lo = fromIdx;
    int hi = toIdx - 1;
    int mid = fromIdx + (hi - lo) / 2;

    if (compareFn(pObj, lo, mid) > 0)
    {
        swapFn(pObj, lo, mid);
    }
    if (compareFn(pObj, mid, hi) > 0)
    {
        swapFn(pObj, mid, hi);
        if (compareFn(pObj, lo, mid) > 0)
        {
            swapFn(pObj, lo, mid);
        }
    }

    for (;;)
    {
        while (compareFn(pObj, lo, mid) < 0)
        {
            lo++;
        }
        while (compareFn(pObj, mid, hi) < 0)
        {
            hi--;
        }
        if (lo >= hi)
        {
            return hi + 1;
        }

        swapFn(pObj, lo, hi);

        // if mid is swapped, update mid.
        if (lo == mid)
        {
            mid = hi;
        }
        else if (hi == mid)
        {
            mid = lo;
        }

        lo++;
        hi--;
    }
}

void quickSort(void *pObj, int fromIdx, int toIdx,
    int (*compareFn)(void *pObj, int fromIdx, int toIdx),
    void (*swapFn)(void *pObj, int fromIdx, int toIdx))
{
    if (toIdx - fromIdx <= 1)
    {
        return;
    }
    int partIdx = partition(pObj, fromIdx, toIdx, compareFn, swapFn);
    quickSort(pObj, fromIdx, partIdx, compareFn, swapFn);
    quickSort(pObj, partIdx, toIdx, compareFn, swapFn);
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

    quickSort(d, 0, DATA_COUNT, mycompare, myswap);

    for (i = 0; i < DATA_COUNT; i++)
    {
        printf("%d\n", d[i]);
    }

    return EXIT_SUCCESS;
}
