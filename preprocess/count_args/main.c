
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

// see https://in-neuro.hatenablog.com/entry/2020/10/21/155651
#define INDEX_RSEQ() \
    4, 3, 2, 1, 0

#define VA_ARGS_SIZE_IMPL( \
    ARG1, ARG2, ARG3, ARG4, N, ...) N

#define VA_ARGS_SIZE_AUX(...) \
    VA_ARGS_SIZE_IMPL(__VA_ARGS__)

#define VA_ARGS_SIZE(...) \
    VA_ARGS_SIZE_AUX(__VA_ARGS__, INDEX_RSEQ())

#define VA_ARGS_SIZE_DUMP_IMPL(...) \
    #__VA_ARGS__

#define VA_ARGS_SIZE_DUMP_AUX(...) \
    VA_ARGS_SIZE_DUMP_IMPL(__VA_ARGS__)

#define VA_ARGS_SIZE_DUMP(...) \
    VA_ARGS_SIZE_DUMP_AUX(__VA_ARGS__, INDEX_RSEQ())

int main(int argc, char *argv[])
{
    int a, b, c, d;
    printf("VA_ARGS_SIZE(): %d\n", VA_ARGS_SIZE()); // 1
    printf("VA_ARGS_SIZE(a): %d\n", VA_ARGS_SIZE(a));
    printf("VA_ARGS_SIZE(a, b): %d\n", VA_ARGS_SIZE(a, b));
    printf("VA_ARGS_SIZE(a, b, c): %d\n", VA_ARGS_SIZE(a, b, c));
    printf("VA_ARGS_SIZE(a, b, c, d): %d\n", VA_ARGS_SIZE(a, b, c, d));

    printf("VA_ARGS_SIZE_DUMP(): %s\n", VA_ARGS_SIZE_DUMP()); // 1
    printf("VA_ARGS_SIZE_DUMP(a): %s\n", VA_ARGS_SIZE_DUMP(a));
    printf("VA_ARGS_SIZE_DUMP(a, b): %s\n", VA_ARGS_SIZE_DUMP(a, b));
    printf("VA_ARGS_SIZE_DUMP(a, b, c): %s\n", VA_ARGS_SIZE_DUMP(a, b, c));
    printf("VA_ARGS_SIZE_DUMP(a, b, c, d): %s\n", VA_ARGS_SIZE_DUMP(a, b, c, d));

    return EXIT_SUCCESS;
}
