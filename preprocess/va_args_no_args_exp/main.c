
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

// '##' is gcc extension.
// see https://gcc.gnu.org/onlinedocs/gcc/Variadic-Macros.html 6.13.10 Macros with a Variable Number of Arguments.
#define SUM(n, ...) sum(n, ##__VA_ARGS__)

int sum(int n, ...)
{
    va_list args;
    va_start(args, n);
    int i;
    int s = 0;

    for (i = 0; i < n; i++)
    {
        s += va_arg(args, int);
    }

    va_end(args);

    return s;
}

int main(int argc, char *argv[])
{
    assert(SUM(0) == 0); // If '##' is not supported, this will cause a compile error.
    assert(SUM(1, 2) == 2);
    assert(SUM(2, 3, 4) == 7);
    printf("OK\n");
    return EXIT_SUCCESS;
}
