#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

int main(int argc, char *argv[])
{
    int opt;
//    while ((opt = getopt(argc, argv, ":abc:d:")) != -1)
    while ((opt = getopt(argc, argv, "abc:d:")) != -1)
    {
        switch (opt)
        {
        case 'a':
            printf("got option 'a'.\n");
            break;

        case 'b':
            printf("got option 'b'.\n");
            break;

        case 'c':
            printf("got option 'c'. str: \"%s\"\n", optarg);
            break;

        case 'd':
            printf("got option 'd'. str: \"%s\"\n", optarg);
            break;

        case '?':
            printf("got option '?'.");
            break;

        default:
            printf("unknown option %c\n", opt);
        }
    }

    int i;
    for (i = 0; i < argc; i++) {
        printf("%d: \"%s\"\n", i, argv[i]);
    }

    return EXIT_SUCCESS;
}
