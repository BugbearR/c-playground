
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

// see https://in-neuro.hatenablog.com/entry/2020/10/21/155651

#define STRINGIZE_AUX(x) #x

#define STRINGIZE(x) STRINGIZE_AUX(x)

#define CONCATENATE_AUX(x, y) x##y

#define CONCATENATE(x, y) CONCATENATE_AUX(x, y)

#define INDEX_RSEQ() \
    4, 3, 2, 1, 0

#define VA_ARGS_SIZE_IMPL( \
    ARG1, ARG2, ARG3, ARG4, N, ...) N

#define VA_ARGS_SIZE_AUX(...) \
    VA_ARGS_SIZE_IMPL(__VA_ARGS__)

#define VA_ARGS_SIZE(...) \
    VA_ARGS_SIZE_AUX(__VA_ARGS__, INDEX_RSEQ())

#define FOR_EACH_VA_ARGS_AUX_1(FUNCTOR, ARG1) FUNCTOR(ARG1)
#define FOR_EACH_VA_ARGS_AUX_2(FUNCTOR, ARG1, ...) FUNCTOR(ARG1) FOR_EACH_VA_ARGS_AUX_1(FUNCTOR, __VA_ARGS__)
#define FOR_EACH_VA_ARGS_AUX_3(FUNCTOR, ARG1, ...) FUNCTOR(ARG1) FOR_EACH_VA_ARGS_AUX_2(FUNCTOR, __VA_ARGS__)
#define FOR_EACH_VA_ARGS_AUX_4(FUNCTOR, ARG1, ...) FUNCTOR(ARG1) FOR_EACH_VA_ARGS_AUX_3(FUNCTOR, __VA_ARGS__)

#define FOR_EACH_VA_ARGS(FUNCTOR, ...) \
    CONCATENATE(FOR_EACH_VA_ARGS_AUX_, VA_ARGS_SIZE(__VA_ARGS__))(FUNCTOR, __VA_ARGS__)

#define DEBUG_PRINT_AUX(x) \
    printf(", %s = %d", STRINGIZE(x), x);

#define DEBUG_PRINT(...) \
    do { \
        printf("line: %d", __LINE__); \
        FOR_EACH_VA_ARGS(DEBUG_PRINT_AUX, __VA_ARGS__); \
        printf("\n"); \
    } while (0)

int main(int argc, char *argv[])
{
    int a, b, c, d;
    a = 10;
    b = 20;
    c = 30;
    d = 40;

    DEBUG_PRINT(a, b, c, d);

    return EXIT_SUCCESS;
}
