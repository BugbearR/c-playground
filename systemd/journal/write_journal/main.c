#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-journal.h>

int main(int argc, char *argv[])
{
    int myResult = EXIT_FAILURE;
    int subResult;
    int myErrno;
    struct iovec *pIovec = NULL;
    int i;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s key1=value1 [key2=value2 ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int itemCount = argc - 1;
    pIovec = calloc(itemCount, sizeof(struct iovec));
    if (!pIovec)
    {
        perror("calloc");
        return EXIT_FAILURE;
    }

    for (i = 0; i < itemCount; i++)
    {
        pIovec[i].iov_base = argv[i + 1];
        pIovec[i].iov_len = strlen(argv[i + 1]);
    }

    subResult = sd_journal_sendv(pIovec, itemCount);
    if (subResult < 0)
    {
        myErrno = -subResult;
        fprintf(stderr, "sd_journal_sendv:%s\n", strerror(myErrno));
        goto EXIT_FUNC;
    }

    myResult = EXIT_FAILURE;

EXIT_FUNC:
    if (pIovec)
    {
        free(pIovec);
    }

    return myResult;
}
