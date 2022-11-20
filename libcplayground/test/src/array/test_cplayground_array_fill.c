#include <cplayground/array.h>

#include <assert.h>
#include <stdint.h>

void test_cplayground_array_fill_all()
{
    int32_t n[4];
    int32_t v = 0x87654321;

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;

    cplayground_array_fill(n, sizeof(n[0]), 0, 3, &v);
    assert(n[0] == v);
    assert(n[1] == v);
    assert(n[2] == v);
    assert(n[3] == 0xabcdef12);
}

void test_cplayground_array_fill_part()
{
    int32_t n[4];
    int32_t v = 0x87654321;

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;

    cplayground_array_fill(n, sizeof(n[0]), 1, 2, &v);
    assert(n[0] == 0x12345678);
    assert(n[1] == v);
    assert(n[2] == v);
    assert(n[3] == 0xabcdef12);
}

void test_cplayground_array_fill_none()
{
    int32_t n[4];
    int32_t v = 0x87654321;

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;

    cplayground_array_fill(n, sizeof(n[0]), 1, 0, &v);
    assert(n[0] == 0x12345678);
    assert(n[1] == 0x9abcdef1);
    assert(n[2] == 0x23456789);
    assert(n[3] == 0xabcdef12);
}

void test_cplayground_array_fill()
{
    test_cplayground_array_fill_all();
    test_cplayground_array_fill_part();
    test_cplayground_array_fill_none();
}
