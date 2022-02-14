#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("%zu\n", sizeof("x"));
    printf("%zu\n", sizeof("Hello, world!"));
    return EXIT_SUCCESS;
}
