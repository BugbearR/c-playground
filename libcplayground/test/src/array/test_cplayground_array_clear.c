#include <cplayground/array.h>

#include <assert.h>
#include <stdint.h>

void test_cplayground_array_clear_all()
{
    int32_t n[4];

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;

    cplayground_array_clear(n, sizeof(n[0]), 0, 3);
    assert(n[0] == 0);
    assert(n[1] == 0);
    assert(n[2] == 0);
    assert(n[3] == 0xabcdef12);
}

void test_cplayground_array_clear_part()
{
    int32_t n[4];

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;

    cplayground_array_clear(n, sizeof(n[0]), 1, 2);
    assert(n[0] == 0x12345678);
    assert(n[1] == 0);
    assert(n[2] == 0);
    assert(n[3] == 0xabcdef12);
}

void test_cplayground_array_clear_none()
{
    int32_t n[4];

    n[0] = 0x12345678;
    n[1] = 0x9abcdef1;
    n[2] = 0x23456789;
    n[3] = 0xabcdef12;

    cplayground_array_clear(n, sizeof(n[0]), 1, 0);
    assert(n[0] == 0x12345678);
    assert(n[1] == 0x9abcdef1);
    assert(n[2] == 0x23456789);
    assert(n[3] == 0xabcdef12);
}

void test_cplayground_array_clear()
{
    test_cplayground_array_clear_all();
    test_cplayground_array_clear_part();
    test_cplayground_array_clear_none();
}
