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

    dst = malloc(dstLen + 1);

    memset(dst, 'X', dstLen + 1);

    printf("&dst[0]: %p\n", &dst[0]);

    printf("snprintf(dst, %zu, \"%s\", \"%s\");\n", dstLen, format, s);
    r = snprintf(dst, dstLen, format, s);
    printf("return: %d\n", r);
    printf("dst:");
    dump(dst, dstLen + 1);
    printf("\n");
    printf("\n");

    free(dst);
}

int main(void)
{
    test(3, "%-2.2s", "");
    test(3, "%-2.2s", "A");
    test(3, "%-2.2s", "AB");
    test(3, "%-2.2s", "ABC");

    test(3, "%2.2s", "");
    test(3, "%2.2s", "A");
    test(3, "%2.2s", "AB");
    test(3, "%2.2s", "ABC");

    test(3, "%.2s", "");
    test(3, "%.2s", "A");
    test(3, "%.2s", "AB");
    test(3, "%.2s", "ABC");

    test(3, "%-2s", "");
    test(3, "%-2s", "A");
    test(3, "%-2s", "AB");
    test(3, "%-2s", "ABC");

    test(3, "%2s", "");
    test(3, "%2s", "A");
    test(3, "%2s", "AB");
    test(3, "%2s", "ABC");

    test(3, "%s", "");
    test(3, "%s", "A");
    test(3, "%s", "AB");
    test(3, "%s", "ABC");

    return EXIT_SUCCESS;
}
