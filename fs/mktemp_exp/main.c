#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int myerrno;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <template>\n", argv[0]);
        return EXIT_FAILURE;
    }
    printf("argv[1] %p:[%s]\n", argv[1], argv[1]);

    // don't use mktemp() in production code
    // use mkstemp() or tmpfile() instead
    char *pTemp = mktemp(argv[1]);
    if (!pTemp) {
        myerrno = errno;
        perror("mktemp");
        printf("errno = %d\n", myerrno);
        return EXIT_FAILURE;
    }
    printf("argv[1] %p:[%s]\n", argv[1], argv[1]);
    printf("%p:[%s]\n", pTemp, pTemp);

    char *pTemp2 = mktemp(argv[1]);
    if (!pTemp2) {
        myerrno = errno;
        perror("mktemp");
        printf("errno = %d\n", myerrno);
        return EXIT_FAILURE;
    }
    printf("argv[1] %p:[%s]\n", argv[1], argv[1]);
    printf("%p:[%s]\n", pTemp2, pTemp2);

    return EXIT_SUCCESS;
}
