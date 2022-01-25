#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    MyFalse = 0,
    MyTrue
} MyBool;

int main(int argc, char *argv[])
{
    MyBool x;
    x = MyFalse;
    printf("%d\n", x);
    x = MyTrue;
    printf("%d\n", x);
    x = !MyFalse;
    printf("%d\n", x);
    x = !MyTrue;
    printf("%d\n", x);

    if (MyFalse)
    {
        printf("MyFalse NG\n");
    }
    else
    {
        printf("MyFalse OK\n");
    }

    if (MyTrue)
    {
        printf("MyTrue OK\n");
    }
    else
    {
        printf("MyTrue NG\n");
    }

    return EXIT_SUCCESS;
}
