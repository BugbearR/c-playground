#include <cplayground/charz.h>

#include <assert.h>

void test_cplayground_charz_isBlank()
{
    assert(cplayground_charz_isBlank(""));
    assert(cplayground_charz_isBlank(" "));
    assert(!cplayground_charz_isBlank("X"));
    assert(cplayground_charz_isBlank("  "));
    assert(!cplayground_charz_isBlank(" X"));
    assert(!cplayground_charz_isBlank("X "));
    assert(cplayground_charz_isBlank("   "));
    assert(!cplayground_charz_isBlank("X  "));
    assert(!cplayground_charz_isBlank(" X "));
    assert(!cplayground_charz_isBlank("  X"));
}
