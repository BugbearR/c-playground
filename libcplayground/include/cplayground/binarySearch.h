#ifndef CPLAYGROUND_BINARYSEARCH_H_
#define CPLAYGROUND_BINARYSEARCH_H_

#include <stdbool.h>

#define cplayground_DEFINE_BINARY_SEARCH_DECL(T) T cplayground_binarySearch_##T(T ok, T ng, bool (*fn)(T value, void *pInfo), void *pInfo)
#define cplayground_DEFINE_BINARY_SEARCH_IMPL(T) \
{ \
    T a = ok; \
    T b = ng; \
    T a_lt_b = (a < b); \
    while ((a_lt_b ? (b - a) : (a - b)) > 1) \
    { \
        T m = a_lt_b ? (a + (b - a) / 2) : (b + (a - b) / 2); \
        if (fn(m, pInfo)) { a = m; } else { b = m; } \
    } \
    return a; \
}

cplayground_DEFINE_BINARY_SEARCH_DECL(int);

#endif /* CPLAYGROUND_BINARYSEARCH_H_ */
