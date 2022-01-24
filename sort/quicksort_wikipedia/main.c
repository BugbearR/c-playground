#include <stdio.h>
#include <stdlib.h>

#define DATA_COUNT (100)

int mycompare(const void *p1, const void *p2)
{
    int d1 = *(int *)p1;
    int d2 = *(int *)p2;
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;
    return 0;
}

// === Wikipedia source start
// see https://ja.wikipedia.org/wiki/%E3%82%AF%E3%82%A4%E3%83%83%E3%82%AF%E3%82%BD%E3%83%BC%E3%83%88
// LICENCE: Creative Commons Attribution-ShareAlike 3.0 (CC-BY-SA 3.0)

/**
 * 値を交換する
 * @param x  - 交換するデータのポインタ
 * @param y  - 交換するデータのポインタ
 * @param sz - データサイズ
 */
void
swap(
    void* x,
    void* y,
    size_t sz
) {
    char* a = x;
    char* b = y;
    while (sz > 0) {
        char t = *a;
        *a++ = *b;
        *b++ = t;
        sz--;
    }
}

/** 分割関数
 *
 * 配列をピボットによって分割し、分割位置を返す。
 * @param a   - 分割する配列
 * @param cmp - 比較関数へのポインタ
 * @param sz  - データサイズ
 * @param n   - 要素数
 * @returns 分割位置を示すポインタ
 */
void*
partition(
    void* a,
    int (*cmp)(void const*, void const*),
    size_t sz,
    size_t n
) {
    // void* に対して直接ポインタ演算はできないので予め char* へ変換する
    char* const base = a;
    if (n <= 1) return base + sz;
    char* lo = base;
    char* hi = &base[sz * (n - 1)];
    char* m  = lo + sz * ((hi - lo) / sz / 2);
    // m が median-of-3 を指すようソート
    if (cmp(lo, m) > 0) {
        swap(lo, m, sz);
    }
    if (cmp(m, hi) > 0) {
        swap(m, hi, sz);
        if (cmp(lo, m) > 0) {
            swap(lo, m, sz);
        }
    }
    while (1) {
        while (cmp(lo, m) < 0) lo += sz; // ピボット以上の要素を下から探す
        while (cmp(m, hi) < 0) hi -= sz; // ピボット以下の要素を上から探す
        if (lo >= hi) return hi + sz;
        swap(lo, hi, sz);
        // ピボットがスワップされた場合、スワップ先を指すよう m を更新する
        if (lo == m) {
            m = hi;
        } else if (hi == m) {
            m = lo;
        }
        lo += sz;
        hi -= sz;
    }
}

/** クイックソート
 *
 * @param a   - ソートする配列
 * @param cmp - 比較関数へのポインタ
 * @param sz  - データサイズ
 * @param n   - 要素数
 */
void
quicksort(
    void* a,
    int (*cmp)(void const*, void const*),
    size_t sz,
    size_t n
) {
    if (n <= 1) return;
    char* p = partition(a, cmp, sz, n);
    char* const base = a;
    size_t n_lo = (p - base) / sz;
    size_t n_hi = (&base[sz * n] - p) / sz;
    printf("n_lo:%zu, n_hi:%zu\n", n_lo, n_hi);
    quicksort(a, cmp, sz, n_lo); // 左側をソート
    quicksort(p, cmp, sz, n_hi); // 右側をソート
}

// === Wikipedia source end

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
        d[i] = DATA_COUNT - i;
    }

    quicksort(d, mycompare, sizeof(int), DATA_COUNT);

    for (i = 0; i < DATA_COUNT; i++)
    {
        printf("%d\n", d[i]);
    }

    return EXIT_SUCCESS;
}
