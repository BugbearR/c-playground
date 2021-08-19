#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int myErrno = atoi(argv[1]);
    printf("%s\n", strerror(myErrno));
    return EXIT_SUCCESS;
}
