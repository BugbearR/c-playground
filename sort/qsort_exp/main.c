#include <stdio.h>
#include <stdlib.h>

#define DATA_COUNT (100)

int mycompare(const void *p1, const void *p2)
{
    int d1 = *(int *)p1;
    int d2 = *(int *)p2;
    if (d1 < d2) return -1;
    if (d1 > d2) return 1;
    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int seed;
    int i;
    int d[DATA_COUNT];

    if (argc >= 2)
    {
        sscanf(argv[1], "%u", &seed);
        srand(seed);
    }

    for (i = 0; i < DATA_COUNT; i++)
    {
        d[i] = rand();
    }

    qsort(d, DATA_COUNT, sizeof(int), mycompare);

    for (i = 0; i < DATA_COUNT; i++)
    {
        printf("%d\n", d[i]);
    }

    return EXIT_SUCCESS;
}
