#include <cplayground/charz.h>

#include <assert.h>
#include <string.h>

void test_cplayground_charz_trimStart_Empty()
{
    char s[] = "";
    assert(cplayground_charz_trimStart(s) == &s[0]);
    assert(strcmp(s, "") == 0);
}

void test_cplayground_charz_trimStart_NoSpace()
{
    char s[] = "ABC";
    assert(cplayground_charz_trimStart(s) == &s[0]);
    assert(strcmp(s, "ABC") == 0);
}

void test_cplayground_charz_trimStart_SpaceOnly1()
{
    char s[] = " ";
    assert(cplayground_charz_trimStart(s) == &s[0]);
    assert(strcmp(s, "") == 0);
}

void test_cplayground_charz_trimStart_SpaceOnly2()
{
    char s[] = "  ";
    assert(cplayground_charz_trimStart(s) == &s[0]);
    assert(strcmp(s, "") == 0);
}

void test_cplayground_charz_trimStart_Space1()
{
    char s[] = " ABC";
    assert(cplayground_charz_trimStart(s) == &s[0]);
    assert(strcmp(s, "ABC") == 0);
}

void test_cplayground_charz_trimStart_Space2()
{
    char s[] = "  ABC";
    assert(cplayground_charz_trimStart(s) == &s[0]);
    assert(strcmp(s, "ABC") == 0);
}

void test_cplayground_charz_trimStart()
{
    test_cplayground_charz_trimStart_Empty();
    test_cplayground_charz_trimStart_NoSpace();
    test_cplayground_charz_trimStart_SpaceOnly1();
    test_cplayground_charz_trimStart_SpaceOnly2();
    test_cplayground_charz_trimStart_Space1();
    test_cplayground_charz_trimStart_Space2();
}
