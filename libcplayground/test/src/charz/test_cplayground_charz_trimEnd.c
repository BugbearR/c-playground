#include <cplayground/charz.h>

#include <assert.h>
#include <string.h>

void test_cplayground_charz_trimEnd_Empty()
{
    char s[] = "";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "") == 0);
}

void test_cplayground_charz_trimEnd_NoSpace()
{
    char s[] = "ABC";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "ABC") == 0);
}

void test_cplayground_charz_trimEnd_SpaceOnly1()
{
    char s[] = " ";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "") == 0);
}

void test_cplayground_charz_trimEnd_SpaceOnly2()
{
    char s[] = "  ";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "") == 0);
}

void test_cplayground_charz_trimEnd_Space1()
{
    char s[] = "ABC ";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "ABC") == 0);
}

void test_cplayground_charz_trimEnd_Space2()
{
    char s[] = "ABC  ";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "ABC") == 0);
}

void test_cplayground_charz_trimEnd_MiddleSpace()
{
    char s[] = "A B C";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, "A B C") == 0);
}

void test_cplayground_charz_trimEnd_StartMiddleEndSpace()
{
    char s[] = " A B C ";
    assert(cplayground_charz_trimEnd(s) == &s[0]);
    assert(strcmp(s, " A B C") == 0);
}

void test_cplayground_charz_trimEnd()
{
    test_cplayground_charz_trimEnd_Empty();
    test_cplayground_charz_trimEnd_NoSpace();
    test_cplayground_charz_trimEnd_SpaceOnly1();
    test_cplayground_charz_trimEnd_SpaceOnly2();
    test_cplayground_charz_trimEnd_Space1();
    test_cplayground_charz_trimEnd_Space2();
    test_cplayground_charz_trimEnd_MiddleSpace();
    test_cplayground_charz_trimEnd_StartMiddleEndSpace();
}
