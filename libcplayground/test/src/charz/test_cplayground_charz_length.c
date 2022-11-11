#include <cplayground/charz.h>

#include <assert.h>

void test_cplayground_charz_length()
{
    assert(cplayground_charz_length("") == 0);
    assert(cplayground_charz_length("A") == 1);
    assert(cplayground_charz_length("AB") == 2);
}
