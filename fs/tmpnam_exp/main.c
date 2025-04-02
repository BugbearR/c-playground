#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char *argv[])
{
    // don't use tmpnam() in production code
    // use mkstemp() or tmpfile() instead
    char buf[PATH_MAX];

    char *pName = tmpnam(buf);
    if (pName == NULL)
    {
        perror("tmpnam");
        return EXIT_FAILURE;
    }

    printf("%s\n", buf);
    printf("%p:%s\n", pName, pName);

    char *pName2 = tmpnam(NULL);
    if (pName2 == NULL)
    {
        perror("tmpnam");
        return EXIT_FAILURE;
    }

    printf("%s\n", buf);
    printf("%p:%s\n", pName2, pName2);

    char *pName3 = tmpnam(NULL);
    if (pName3 == NULL)
    {
        perror("tmpnam");
        return EXIT_FAILURE;
    }

    printf("%s\n", buf);
    printf("%p:%s\n", pName3, pName3);

    return EXIT_SUCCESS;
}
