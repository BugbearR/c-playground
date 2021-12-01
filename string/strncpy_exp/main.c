#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(int argc, char argv[1])
{
    char buf[4];
    char src[] = "AB";
    char *p;
    int i;
    int j;

    for (i = 0; i <= 3; i++)
    {
        printf("&buf: %p\n", buf);
        printf("strncpy(buf, src, %d);\n", i);
        memset(buf, 'X', sizeof(buf));
        p = strncpy(buf, src, i);
        printf("return: %p\n", p);
        printf("buf:");
        for (j = 0; j < 4; j++)
        {
            printf(" %02hhx", buf[j]);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
