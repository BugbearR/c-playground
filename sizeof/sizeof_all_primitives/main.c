#include <stdio.h>
#include <stdlib.h>

#define PRINT_SIZEOF(t) printf(#t ": %zu\n", sizeof(t))

int main(int argc, char *argv[])
{
    PRINT_SIZEOF(char);
    PRINT_SIZEOF(signed char);
    PRINT_SIZEOF(unsigned char);
    PRINT_SIZEOF(short);
    PRINT_SIZEOF(unsigned short);
    PRINT_SIZEOF(int);
    PRINT_SIZEOF(unsigned int);
    PRINT_SIZEOF(long);
    PRINT_SIZEOF(unsigned long);
    PRINT_SIZEOF(long long);
    PRINT_SIZEOF(unsigned long long);
    PRINT_SIZEOF(float);
    PRINT_SIZEOF(double);
    PRINT_SIZEOF(long double);
    PRINT_SIZEOF(void *);
    return EXIT_SUCCESS;
}
