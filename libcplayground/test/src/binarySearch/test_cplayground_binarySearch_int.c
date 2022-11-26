#include <cplayground/binarySearch.h>
#include <cplayground/base.h>
#include <assert.h>

#include <stddef.h>
#include <limits.h>

bool solve0(int n, void *pInfo) {
    cplayground_UNUSED(pInfo);
    return n < 1;
}

bool solve1(int n, void *pInfo) {
    cplayground_UNUSED(pInfo);
    return n < 2;
}

bool solveHalf(int n, void *pInfo) {
    cplayground_UNUSED(pInfo);
    return n < INT_MAX/2;
}

void test_cplayground_binarySearch_int() {
    assert(cplayground_binarySearch_int(0, 1, solve0, NULL) == 0);
    assert(cplayground_binarySearch_int(0, 2, solve0, NULL) == 0);
    assert(cplayground_binarySearch_int(0, 2, solve1, NULL) == 1);
    assert(cplayground_binarySearch_int(1, 2, solve1, NULL) == 1);
    assert(cplayground_binarySearch_int(1, 3, solve1, NULL) == 1);

    assert(cplayground_binarySearch_int(0, INT_MAX, solve0, NULL) == 0);
    assert(cplayground_binarySearch_int(0, INT_MAX, solveHalf, NULL) == INT_MAX/2 - 1);
    assert(cplayground_binarySearch_int(INT_MIN / 2, INT_MAX / 2, solve0, NULL) == 0);
    assert(cplayground_binarySearch_int(INT_MIN / 2, INT_MAX / 2, solve1, NULL) == 1);
}
