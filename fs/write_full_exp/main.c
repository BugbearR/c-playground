#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DATA_LEN (2*1024*1024)

int writeFullExp(const char *pDstPath)
{
    int myResult = -1;
    int dstFd = -1;
    char *pBuf = NULL;
    int i;
    int myErrno;

    pBuf = malloc(DATA_LEN);
    if (!pBuf)
    {
        perror("malloc");
        goto EXIT_FUNC;
    }

    dstFd = open(pDstPath, O_CREAT | O_EXCL | O_WRONLY, 0666);
    if (dstFd == -1)
    {
        perror("open");
        goto EXIT_FUNC;
    }

    size_t leftLen = DATA_LEN;
    while (leftLen > 0)
    {
        ssize_t writeResultLen = write(dstFd, pBuf, leftLen);
        if (writeResultLen == -1)
        {
            myErrno = errno;
            if (myErrno == EINTR)
            {
                printf("EINTR\n");
                continue;
            }
            else if (myErrno == EAGAIN)
            {
                printf("EAGAIN\n");
                continue;
            }
            else if (myErrno == EWOULDBLOCK)
            {
                printf("EWOULDBLOCK\n");
                continue;
            }
            else
            {
                printf("errno:%d, strerror:%s\n", myErrno, strerror(myErrno));
                goto EXIT_FUNC;
            }
        }
        else
        {
            printf("writeResultLen: %zd\n", writeResultLen);
            leftLen -= writeResultLen;
        }
    }

    myResult = 0;
EXIT_FUNC:
    if (dstFd != -1)
    {
        close(dstFd);
    }

    return myResult;
}

int main(int argc, char *argv[])
{
    int subResult;
    int subError;
    char *pSrcPath = NULL;
    char *pDstPath = NULL;
    mode_t mode;

    if (argc < 2) {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    pDstPath = argv[1];

    subResult = writeFullExp(pDstPath);
    if (subResult != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
