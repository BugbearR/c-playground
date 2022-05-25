#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Sample_tag
{
    char a[8];
    char b[1];
    char c[8];
    char d[1];
    char e[8];
    char f[1];
} Sample_t;

int main(int argc, char *argv[])
{
    Sample_t o;
    memset(&o, 0, sizeof(o));
    strncpy(o.a, "aaaaaaaaa", sizeof(o.a));
    strncpy(o.b, "b", sizeof(o.b));
    strncpy(o.c, "ccccccccc", sizeof(o.c));
    strncpy(o.d, "d", sizeof(o.d));
    strncpy(o.e, "eeeeeeeee", sizeof(o.e));

    printf("size: %zu\n", sizeof(o));
    printf("strlen(o.a): %zu\n", strlen(o.a));
    printf("strlen(o.b): %zu\n", strlen(o.b));
    printf("strlen(o.c): %zu\n", strlen(o.c));
    printf("strlen(o.d): %zu\n", strlen(o.d));
    printf("strlen(o.e): %zu\n", strlen(o.e));
    printf("strlen(o.f): %zu\n", strlen(o.f));

    return EXIT_SUCCESS;
}
