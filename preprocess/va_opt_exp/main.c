
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

// __VA_OPT__ since C23
#define SUM(n, ...) sum(n __VA_OPT__(,) __VA_ARGS__)

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
    assert(SUM(0) == 0); // If '__VA_OPT__' is not supported, this will cause a compile error.
    assert(SUM(1, 2) == 2);
    assert(SUM(2, 3, 4) == 7);
    printf("OK\n");
    return EXIT_SUCCESS;
}
