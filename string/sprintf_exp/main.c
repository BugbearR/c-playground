#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void dump(char *p, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
    {
        printf(" %02hhx", p[i]);
    }
}

void test(size_t dstLen, const char *format, const char *s)
{
    char *dst;
    int r;

    dst = malloc(dstLen);

    memset(dst, 'X', dstLen);

    printf("&dst[0]: %p\n", &dst[0]);

    printf("sprintf(dst, \"%s\", \"%s\");\n", format, s);
    r = sprintf(dst, format, s);
    printf("return: %d\n", r);
    printf("dst:");
    dump(dst, dstLen);
    printf("\n");
    printf("\n");

    free(dst);
}

int main(void)
{
    test(5, "%-2.2s", "");
    test(5, "%-2.2s", "A");
    test(5, "%-2.2s", "AB");
    test(5, "%-2.2s", "ABC");

    test(5, "%2.2s", "");
    test(5, "%2.2s", "A");
    test(5, "%2.2s", "AB");
    test(5, "%2.2s", "ABC");

    test(5, "%.2s", "");
    test(5, "%.2s", "A");
    test(5, "%.2s", "AB");
    test(5, "%.2s", "ABC");

    return EXIT_SUCCESS;
}
