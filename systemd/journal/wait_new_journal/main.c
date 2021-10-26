#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-journal.h>
#include <errno.h>
#include <signal.h>

typedef void (*my_sighandler_t)(int);

volatile sig_atomic_t g_sigNo = 0;

void signalHandler(int sigNo)
{
    g_sigNo = sigNo;
}

int main(void)
{
    int subResult;
    int myErrno;
    sd_journal *j = NULL;
    my_sighandler_t oldHandler;

    oldHandler = signal(SIGUSR1, signalHandler);
    if (oldHandler == SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }

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
            // sd_journal_wait doesn't return EINTR
            subResult = sd_journal_wait(j, (uint64_t) 10000000);
            if (subResult < 0)
            {
                myErrno = -subResult;
                fprintf(stderr, "sd_journal_wait:%s\n", strerror(myErrno));
            }
            continue;
        }

        subResult = sd_journal_get_data(j, "MESSAGE", &pData, &dataLen);
        if (subResult != 0) {
            myErrno = -subResult;
            fprintf(stderr, "sd_journal_get_data:%s\n", strerror(myErrno));
        }
        else {
            printf("MESSAGE: %.*s\n", (int)dataLen, (const char *)pData);
        }
    }

EXIT_FUNC:
    if (j)
    {
        sd_journal_close(j);
    }

    return EXIT_SUCCESS;
}
