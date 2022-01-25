#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <float.h>

int main(int argc, char *argv[])
{
    {
        _Bool x;
        x = 0;
        printf("%d\n", x);
        x = 1;
        printf("%d\n", x);
        x = false;
        printf("%d\n", x);
        x = true;
        printf("%d\n", x);
        x = !false;
        printf("%d\n", x);
        x = !true;
        printf("%d\n", x);
    }

    {
        bool x;
        x = 0;
        printf("%d\n", x);
        x = 1;
        printf("%d\n", x);
        x = false;
        printf("%d\n", x);
        x = true;
        printf("%d\n", x);
        x = !false;
        printf("%d\n", x);
        x = !true;
        printf("%d\n", x);
    }

    if (false)
    {
        printf("false NG\n");
    }
    else
    {
        printf("false OK\n");
    }

    if (true)
    {
        printf("true OK\n");
    }
    else
    {
        printf("true NG\n");
    }

    {
        bool r;
        r = (bool) -1;
        printf("%d\n", r);
        r = (bool) 0.0;
        printf("%d\n", r);
        r = (bool) 0.5;
        printf("%d\n", r);
        r = (bool) DBL_MIN;
        printf("%d\n", r);
    }

    return EXIT_SUCCESS;
}
