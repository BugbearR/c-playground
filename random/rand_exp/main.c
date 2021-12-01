#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned int seed;
    int i;

    if (argc >= 2)
    {
        sscanf(argv[1], "%u", &seed);
        srand(seed);
    }

    for (i = 0; i < 10; i++)
    {
        printf("%d\n", rand());
    }

    return EXIT_SUCCESS;
}
