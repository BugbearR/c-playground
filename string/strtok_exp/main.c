#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void dump(char *p, size_t len) {
    size_t i;
    for (i = 0; i < len; i++)
    {
        printf(" %02hhx", p[i]);
    }
}

int main(int argc, char *argv[])
{
    int len;
    char *pLine;
    char *pDelim;
    char *pToken;

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s string delimiter\n", argv[0]);
        return EXIT_FAILURE;
    }

    pLine = argv[1];
    pDelim = argv[2];

    dump(pLine, strlen(pLine) + 1);
    printf("\n");
    printf("pLine: %p\n", pLine);
    errno = 0;
    pToken = strtok(pLine, pDelim);
    while (pToken != NULL) {
        printf("pToken: %p\n", pToken);
        dump(pToken, strlen(pToken) + 1);
        printf("\n");
        pToken = strtok(NULL, pDelim);
    }
    return EXIT_SUCCESS;
}
