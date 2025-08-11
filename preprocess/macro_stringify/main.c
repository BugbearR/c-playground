#include <stdio.h>
#include <stdlib.h>

#define HELLO "Hello"
#define WORLD "world"
#define macro_stringify(s) #s
#define macro_stringify_extract(arg) macro_stringify(arg)

int main(int argc, char *argv[])
{
    printf(macro_stringify(Hello world));
    printf("\n");
    printf(macro_stringify_extract(HELLO WORLD));
    printf("\n");
    return EXIT_SUCCESS;
}
