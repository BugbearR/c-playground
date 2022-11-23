#include <cplayground/array.h>

#include <assert.h>
#include <stdint.h>

void test_cplayground_array_insertSpace_none()
{
    int32_t n[6];

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;
    n[4] = 0x3456789a;
    n[5] = 0xbcdef123;

    cplayground_array_insertSpace(n, sizeof(n[0]), 5, 3, 1, 0);
    assert(n[0] == 0x12345678);
    assert(n[1] == 0x9abcdef1);
    assert(n[2] == 0x23456789);
    assert(n[3] == 0xabcdef12);
    assert(n[4] == 0x3456789a);
    assert(n[5] == 0xbcdef123);
}

void test_cplayground_array_insertSpace_one()
{
    int32_t n[6];

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;
    n[4] = 0x3456789a;
    n[5] = 0xbcdef123;

    cplayground_array_insertSpace(n, sizeof(n[0]), 5, 3, 1, 1);
    assert(n[0] == 0x12345678);
    assert(n[2] == 0x9abcdef1);
    assert(n[3] == 0x23456789);
    assert(n[4] == 0x3456789a);
    assert(n[5] == 0xbcdef123);
}

void test_cplayground_array_insertSpace()
{
    test_cplayground_array_insertSpace_one();
    test_cplayground_array_insertSpace_none();
}
