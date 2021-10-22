#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-journal.h>
#include <errno.h>

int main(void)
{
    int subResult;
    int myErrno;
    sd_journal *j = NULL;

    subResult = sd_journal_open(&j, 0);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_open:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    // subResult = sd_journal_seek_tail(j);
    // if (subResult < 0)
    // {
    //     myErrno = -subResult;
    //     if (myErrno == EADDRNOTAVAIL)
    //     {
    //         fprintf(stderr, "sd_journal_seek_tail:%s\n", strerror(myErrno));
    //     }
    //     else
    //     {
    //         fprintf(stderr, "sd_journal_seek_tail:%s\n", strerror(myErrno));
    //         // return EXIT_FAILURE;
    //     }
    // }

    // subResult = sd_journal_seek_head(j);
    // if (subResult < 0) {
    //     myErrno = -subResult;
    //     fprintf(stderr, "sd_journal_seek_head:%s\n", strerror(myErrno));
    // }

    for (;;) {
        const void *pData = NULL;
        size_t dataLen = 0;

        printf("----------------------------------------\n");

        subResult = sd_journal_next(j);
        if (subResult < 0) {
            myErrno = -subResult;
            fprintf(stderr, "sd_journal_seek_head:%s\n", strerror(myErrno));
        }
        if (subResult == 0)
        {
            subResult = sd_journal_wait(j, (uint64_t) 1000000);
            if (subResult < 0)
            {
                myErrno = -subResult;
                fprintf(stderr, "sd_journal_wait:%s\n", strerror(myErrno));
            }
            continue;
        }

        subResult = sd_journal_get_data(j, "MESSAGE", &pData, &dataLen);
        printf("MESSAGE: %.*s\n", (int)dataLen, (const char *)pData);
    }

EXIT_FUNC:
    if (j)
    {
        sd_journal_close(j);
    }

    return EXIT_SUCCESS;
}
