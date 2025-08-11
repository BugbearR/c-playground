#include <stdio.h>
#include <stdlib.h>

#define macro_token_concat(s) const char *name##s() { return #s; }
#define macro_token_concat_s(s) const char *name##s##x() { return #s "x"; }

macro_token_concat(A);
macro_token_concat_s(A);

int main(int argc, char *argv[])
{
    printf("%s\n", nameA());
    printf("%s\n", nameAx());
    return EXIT_SUCCESS;
}
