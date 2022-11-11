#include <cplayground/charz.h>

#include <assert.h>

void test_cplayground_charz_isEmpty()
{
    assert(cplayground_charz_isEmpty(""));
    assert(!cplayground_charz_isEmpty("X"));
}
