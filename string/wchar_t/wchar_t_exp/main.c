#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
    wchar_t s[] = L"あ漢"; // ok: gcc 12
    // wchar_t s[] = L"\u3042"; // ok: gcc 12
    // wchar_t s[] = L"\U0010ffff"; // ok: gcc 12
    char *p = (char *)s;
    int i;

    // UTF-32LE: gcc 12
    printf("sizeof(wchar_t): %zu\n", sizeof(wchar_t));

    for (i = 0; i < (int)sizeof(s); i++)
    {
        printf(" %02x", p[i] & 0xff);
    }
    printf("\n");

    return EXIT_SUCCESS;
}
