#include <stdio.h>
#include <stdlib.h>

struct S1
{
    char c;
    short s;
    int i;
    char ca[10];
};

void dumpS1(struct S1 *pS1)
{
    printf("c: %hhd\n", pS1->c);
    printf("s: %hd\n", pS1->s);
    printf("i: %d\n", pS1->i);
    printf("ca: %s\n", pS1->ca);
}

int main(int argc, char *argv[])
{
    struct S1 s1_1 = {0};
    struct S1 s1_2 = {
        .s = 123,
        .ca = "Hello!"
    };
    dumpS1(&s1_1);
    dumpS1(&s1_2);

    // Complex literal
    s1_2 = (struct S1){
        .c = 12,
        .i = 123,
        .ca = "World!"
    };
    dumpS1(&s1_2);
    s1_2 = (struct S1){0};
    dumpS1(&s1_2);

    return EXIT_SUCCESS;
}
