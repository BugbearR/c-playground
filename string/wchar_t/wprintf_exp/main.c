#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <wchar.h>
#include <locale.h>

int main(int argc, char *argv[])
{
    // see: https://stackoverflow.com/questions/79570946/why-does-wprintf-replace-non-ascii-characters-with-question-mark-character
    // clear C locale
    setlocale(LC_ALL, "");
    wchar_t s[] = L"あ漢";
    char a[] = "あ漢";

    wprintf(L"あ漢\n");
    wprintf(L"%ls\n", s); // gcc 12 ok
    wprintf(L"%s\n", a); // gcc 12 ok

    return EXIT_SUCCESS;
}
