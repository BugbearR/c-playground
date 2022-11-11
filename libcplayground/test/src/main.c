#include <stdlib.h>
#include <stdio.h>
#include "test/cplayground/charz.h"

int main(int argc, char *argv[])
{
    test_cplayground_charz_isBlank();
    test_cplayground_charz_isEmpty();
    test_cplayground_charz_length();

    printf("OK\n");
    return EXIT_SUCCESS;
}
