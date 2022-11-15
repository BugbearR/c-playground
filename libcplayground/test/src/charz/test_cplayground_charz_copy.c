#include <cplayground/charz.h>

#include <assert.h>
#include <string.h>

void test_cplayground_charz_copy()
{
    char dst[3];
    char src[3] = "";
    char dstExpected[3];

    memcpy(src, "ABC", 3);
    src[0] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 0, src);
    memcpy(dstExpected, "XXX", 3);
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[0] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 1, src);
    memcpy(dstExpected, "XXX", 3);
    dstExpected[0] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[0] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 2, src);
    memcpy(dstExpected, "XXX", 3);
    dstExpected[0] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);


    memcpy(src, "ABC", 3);
    src[1] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 0, src);
    memcpy(dstExpected, "XXX", 3);
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[1] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 1, src);
    memcpy(dstExpected, "XXX", 3);
    dstExpected[0] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[1] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 2, src);
    memcpy(dstExpected, "AXX", 3);
    dstExpected[1] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[1] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 3, src);
    memcpy(dstExpected, "AXX", 3);
    dstExpected[1] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);


    memcpy(src, "ABC", 3);
    src[2] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 0, src);
    memcpy(dstExpected, "XXX", 3);
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[2] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 1, src);
    memcpy(dstExpected, "XXX", 3);
    dstExpected[0] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[2] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 2, src);
    memcpy(dstExpected, "AXX", 3);
    dstExpected[1] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);

    memcpy(src, "ABC", 3);
    src[2] = '\0';
    memcpy(dst, "XXX", 3);
    cplayground_charz_copy(dst, 3, src);
    memcpy(dstExpected, "ABX", 3);
    dstExpected[2] = '\0';
    assert(memcmp(dst, dstExpected, sizeof(dstExpected)) == 0);
}
