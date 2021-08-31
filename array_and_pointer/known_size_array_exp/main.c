#include <stdio.h>
#include <stdlib.h>

void func(int x[3])
{
    printf("func sizeof(x): %zu\n", sizeof(x));
    printf("address offset: %zd\n", (char *)(x + 1) - (char *)x);
}

int main(int argc, char *argv[])
{
    int x[3] = { 1, 2, 3 };
    printf("sizeof(x): %zu\n", sizeof(x));
    printf("address offset: %zd\n", (char *)(x + 1) - (char *)x);
    func(x);
    return EXIT_SUCCESS;
}
