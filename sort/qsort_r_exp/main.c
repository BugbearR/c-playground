#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define DATA_COUNT (100)

typedef struct Record {
    int v1;
    int v2;
} Record_t;

typedef struct Context {
    int sw;
} Context_t;

int compareInt(int a, int b)
{
    if (a < b)
        return -1;
    else if (a > b)
        return 1;
    else
        return 0;
}

int mycompare(const void *p1, const void *p2, void *context)
{
    Record_t *pr1 = (Record_t *)p1;
    Record_t *pr2 = (Record_t *)p2;
    Context_t *ctx = (Context_t *)context;

    if (ctx->sw == 0)
    {
        return compareInt(pr1->v1, pr2->v1);
    }
    else
    {
        return compareInt(pr1->v2, pr2->v2);
    }
}

int main(int argc, char *argv[])
{
    unsigned int seed;
    int i;
    Record_t r[DATA_COUNT];

    if (argc >= 2)
    {
        sscanf(argv[1], "%u", &seed);
        srand(seed);
    }

    for (i = 0; i < DATA_COUNT; i++)
    {
        r[i].v1 = rand();
        r[i].v2 = rand();
    }

    printf("sorting by v1\n");
    Context_t context;
    context.sw = 0; // Sort by v1
    qsort_r(r, DATA_COUNT, sizeof(Record_t), mycompare, &context);

    for (i = 0; i < DATA_COUNT; i++)
    {
        printf("%d, %d\n", r[i].v1, r[i].v2);
    }

    printf("sorting by v2\n");
    context.sw = 1; // Sort by v2
    qsort_r(r, DATA_COUNT, sizeof(Record_t), mycompare, &context);

    for (i = 0; i < DATA_COUNT; i++)
    {
        printf("%d, %d\n", r[i].v1, r[i].v2);
    }

    return EXIT_SUCCESS;
}
