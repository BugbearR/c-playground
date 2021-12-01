#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-journal.h>
#include <errno.h>

void putJournalMessage(sd_journal *j) {
    int subResult;
    int myErrno;
    const void *pData;
    size_t dataLen;

    subResult = sd_journal_get_data(j, "MESSAGE", &pData, &dataLen);
    printf("sd_journal_get_data result: %d\n", subResult);
    printf("MESSAGE: %.*s\n", (int)dataLen, (const char *)pData);
}

int main(void)
{
    int subResult;
    int myErrno;
    sd_journal *j = NULL;
    char *pCursor1 = NULL;
    char *pCursor2 = NULL;
    char *pCursor3 = NULL;
    char *pCurCursor = NULL;
    char *pCurCursor2 = NULL;

    subResult = sd_journal_open(&j, 0);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_open:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    printf("========================================\n");
    subResult = sd_journal_next(j);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_seek_head:%s\n", strerror(myErrno));
    }
    printf("sd_journal_next result: %d\n", subResult);

    subResult = sd_journal_get_cursor(j, &pCursor1);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_get_cursor:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    printf("cursor1: \"%s\"\n", pCursor1);

    putJournalMessage(j);

    printf("========================================\n");
    subResult = sd_journal_next(j);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_seek_head:%s\n", strerror(myErrno));
    }
    printf("sd_journal_next result: %d\n", subResult);

    subResult = sd_journal_get_cursor(j, &pCursor2);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_get_cursor:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    printf("cursor2: \"%s\"\n", pCursor2);

    putJournalMessage(j);

    printf("========================================\n");
    subResult = sd_journal_next(j);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_seek_head:%s\n", strerror(myErrno));
    }
    printf("sd_journal_next result: %d\n", subResult);

    subResult = sd_journal_get_cursor(j, &pCursor3);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_get_cursor:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    printf("cursor3: \"%s\"\n", pCursor3);

    putJournalMessage(j);

    printf("========================================\n");
    printf("seek cursor to cursor2\n");
    subResult = sd_journal_seek_cursor(j, pCursor2);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_seek_cursor:%s\n", strerror(myErrno));
    }

    printf("read message before sd_journal_next\n");
    putJournalMessage(j);

    printf("call sd_journal_next\n");
    subResult = sd_journal_next(j);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_next:%s\n", strerror(myErrno));
    }
    printf("sd_journal_next result: %d\n", subResult);

    putJournalMessage(j);

    subResult = sd_journal_get_cursor(j, &pCurCursor);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_get_cursor:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    printf("curCursor: \"%s\"\n", pCurCursor);


   printf("========================================\n");
    printf("seek cursor to cursor2\n");
    subResult = sd_journal_seek_cursor(j, pCursor2);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_seek_cursor:%s\n", strerror(myErrno));
    }

    printf("read message before sd_journal_previous\n");
    putJournalMessage(j);

    printf("call sd_journal_previous\n");
    subResult = sd_journal_previous(j);
    if (subResult < 0) {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_previous:%s\n", strerror(myErrno));
    }
    printf("sd_journal_previous result: %d\n", subResult);

    putJournalMessage(j);

    subResult = sd_journal_get_cursor(j, &pCurCursor2);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_get_cursor:%s\n", strerror(myErrno));
        return EXIT_FAILURE;
    }

    printf("curCursor: \"%s\"\n", pCurCursor2);

EXIT_FUNC:
    if (pCurCursor) {
        free(pCurCursor);
    }

    if (pCurCursor2) {
        free(pCurCursor2);
    }

    if (pCursor3) {
        free(pCursor3);
    }

    if (pCursor2) {
        free(pCursor2);
    }

    if (pCursor1) {
        free(pCursor1);
    }
    sd_journal_close(j);

    return EXIT_SUCCESS;
}
