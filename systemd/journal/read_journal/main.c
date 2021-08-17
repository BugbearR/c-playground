#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-journal.h>

int main(void)
{
    int subResult;
    int myErrno;
    sd_journal *j = NULL;

    subResult = sd_journal_open(&j, 0);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_open:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    subResult = sd_journal_seek_head(j);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_seek_head:%s\n", strerror(myErrno));
        // return EXIT_FAILURE;
    }

    for (;;) {
        subResult = sd_journal_next(j);
        if (subResult < 0) {
            myErrno = -subResult;
            fprintf(stderr, "sd_journal_next:%s\n", strerror(myErrno));
            return EXIT_FAILURE;
        }
        if (subResult == 0) {
            break;
        }

        printf("----------------------------------------\n");
        sd_journal_restart_data(j);

        const void *pData;
        size_t length;
        for (;;) {
            subResult = sd_journal_enumerate_data(j, &pData, &length);
            if (subResult < 0) {
                myErrno = -subResult;
                fprintf(stderr, "sd_journal_enumerate_data:%s\n", strerror(myErrno));
                return EXIT_FAILURE;
            }
            if (subResult == 0) {
                break;
            }
            printf("%.*s\n", (int)length, pData);
        }
    }

EXIT_FUNC:
    sd_journal_close(j);

    return EXIT_SUCCESS;
}
