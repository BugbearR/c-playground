#include <stdlib.h>
#include <stdio.h>
#include <test/cplayground/array.h>
#include <test/cplayground/charz.h>

int main(int argc, char *argv[])
{
    test_cplayground_array_clear();
    test_cplayground_array_fill();
    test_cplayground_array_insertSpace();

    test_cplayground_charz_copy();
    test_cplayground_charz_isBlank();
    test_cplayground_charz_isEmpty();
    test_cplayground_charz_length();
    test_cplayground_charz_trimEnd();
    test_cplayground_charz_trimStart();

    printf("OK\n");
    return EXIT_SUCCESS;
}
