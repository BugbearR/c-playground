#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <regex.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int result = EXIT_FAILURE;
    int subResult;
    int isRegexObjAlive = 0;
    regex_t regexObj;
    FILE *pFile = NULL;
    char buf[4096 + 1];
    char msg[256 + 1];
    char *pLine = NULL;
    int lineNo;
    regmatch_t matches[10];
    int mi;

    if (argc < 3)
    {
        fprintf(stderr, "usage: %s regexp path\n", argv[0]);
        return EXIT_FAILURE;
    }

    subResult = regcomp(&regexObj, argv[1], REG_EXTENDED);
    if (subResult != 0)
    {
        fprintf(stderr, "regcomp error. code:%d\n", subResult);
        regerror(subResult, &regexObj, msg, sizeof(msg));
        fprintf(stderr, "%s\n", msg);
        return EXIT_FAILURE;
    }
    isRegexObjAlive = 1;

    pFile = fopen(argv[2], "rt");

    lineNo = 1;
    for (;;)
    {
        errno = 0;
        pLine = fgets(buf, sizeof(buf), pFile);
        if (!pLine)
        {
            int subErrno = errno;
            if (feof(pFile))
            {
                break;
            }
            fprintf(stderr, "fgets: %s", strerror(subErrno));
            fprintf(stderr, "errno: %d\n", subErrno);
            goto EXIT_FUNC;
        }

        char *p = &buf[0];
        int isFirst = 1;
        for (;;)
        {
            subResult = regexec(&regexObj, p, sizeof(matches)/sizeof(matches[0]), matches, 0);
            if (subResult != 0)
            {
                if (subResult == REG_NOMATCH)
                {
                    break;
                }
                fprintf(stderr, "regexec result: %d\n", subResult);
                regerror(subResult, &regexObj, msg, sizeof(msg));
                fprintf(stderr, "%s\n", msg);
                break;
            }

            if (isFirst)
            {
                printf("line:%d str:%s", lineNo, buf);
                isFirst = 0;
            }
            for (mi = 0; mi < sizeof(matches)/sizeof(matches[0]) && matches[mi].rm_so != -1; mi++)
            {
                printf("i:%d rm_so:%" PRIdMAX " rm_eo:%" PRIdMAX "\n", mi, (intmax_t)matches[mi].rm_so, (intmax_t)matches[mi].rm_eo);
                int len = (int)(matches[mi].rm_eo - matches[mi].rm_so);
                printf("str: \"%.*s\"\n", len, p + matches[mi].rm_so);
            }
            p += matches[0].rm_eo;
        }
    }

    result = EXIT_SUCCESS;

EXIT_FUNC:
    if (isRegexObjAlive) {
        regfree(&regexObj);
    }

    if (pFile)
    {
        fclose(pFile);
    }

    return result;
}
