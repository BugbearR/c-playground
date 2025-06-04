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
    char *pLine1;
    char *pLine2;
    char *pDelim;
    char *pSavePtr1;
    char *pSavePtr2;
    char *pToken1;
    char *pToken2;

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s string1 string2 delimiter\n", argv[0]);
        return EXIT_FAILURE;
    }

    pLine1 = argv[1];
    pLine2 = argv[2];
    pDelim = argv[3];

    printf("pLine1: %p\n", pLine1);
    dump(pLine1, strlen(pLine1) + 1);
    printf("\n");
    printf("pSavePtr1: %p\n", pSavePtr1);
    printf("\n");
    printf("pLine2: %p\n", pLine2);
    dump(pLine2, strlen(pLine2) + 1);
    printf("\n");
    printf("pSavePtr2: %p\n", pSavePtr2);
    printf("\n");

    errno = 0;

    pToken1 = strtok_r(pLine1, pDelim, &pSavePtr1);
    printf("pSavePtr1: %p\n", pSavePtr1);
    pToken2 = strtok_r(pLine2, pDelim, &pSavePtr2);
    printf("pSavePtr2: %p\n", pSavePtr2);
    while (pToken1 != NULL && pToken2 != NULL) {

        if (pToken1 != NULL) {
            printf("pToken1: %p\n", pToken1);
            dump(pToken1, strlen(pToken1) + 1);
            printf("\n");
            pToken1 = strtok_r(NULL, pDelim, &pSavePtr1);
            printf("pSavePtr1: %p\n", pSavePtr1);
        }
        if (pToken2 != NULL) {
            printf("pToken2: %p\n", pToken2);
            dump(pToken2, strlen(pToken2) + 1);
            printf("\n");
            pToken2 = strtok_r(NULL, pDelim, &pSavePtr2);
            printf("pSavePtr2: %p\n", pSavePtr2);
        }
    }
    return EXIT_SUCCESS;
}
