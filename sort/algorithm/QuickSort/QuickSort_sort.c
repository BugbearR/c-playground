#include "QuickSort.h"

static int QuickSort_partition(QuickSort_Ctx_t *pCtx, int fromIdx, int toIdx)
{
    if (toIdx - fromIdx <= 1)
    {
        return fromIdx + 1;
    }

    int lo = fromIdx;
    int hi = toIdx - 1;
    int mid = fromIdx + (hi - lo) / 2;

    // mid = median-of-3
    if (lo < mid && fnCompare(pCtx->pObj, lo, mid) > 0)
    {
        fnSwap(pCtx->pObj, lo, mid);
    }
    if (mid < hi && fnCompare(pCtx->pObj, mid, hi) > 0)
    {
        fnSwap(pCtx->pObj, mid, hi);
        if (lo < mid && fnCompare(pCtx->pObj, lo, mid) > 0)
        {
            fnSwap(pCtx->pObj, lo, mid);
        }
    }

    for (;;)
    {
        while (fnCompare(pCtx->pObj, lo, mid) < 0)
        {
            lo++;
        }
        while (fnCompare(pCtx->pObj, mid, hi) < 0)
        {
            hi--;
        }
        if (lo >= hi)
        {
            return hi + 1;
        }

        fnSwap(pCtx->pObj, lo, hi);

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

int QuickSort_sortImpl(QuickSort_Ctx_t *pCtx, int fromIdx, int toIdx)
{
    int ret;
    int pivotIdx = QuickSort_partition(pCtx->pObj, fromIdx, toIdx);
    if (pivotIdx < 0)
    {
        return pivotIdx;
    }

    ret = QuickSort_sortImpl(pCtx, fromIdx, pivotIdx);
    if (ret != 0)
    {
        return ret;
    }

    ret = QuickSort_sortImpl(pCtx, pivotIdx + 1, toIdx);
    if (ret != 0)
    {
        return ret;
    }

    return 0;
}

int QuickSort_sort(
    void *pObj,
    int count,
    int (*fnCompare)(void *pObj, int idx1, int idx2),
    void (*fnSwap)(void *pObj, int idx1, int idx2)
) {

    QuickSort_Ctx_t ctx = {
        .pObj = pObj,
        .fnSwap = fnSwap,
        .fnCompare = fnCompare
    };

    return QuickSort_sortImpl(&ctx, 0, count);
}
