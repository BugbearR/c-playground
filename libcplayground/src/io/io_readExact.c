#include <cplayground/io.h>

#include <unistd.h>

int cplayground_io_readExact(int fd, char *pBuf, size_t bufLen, size_t *pResultLen)
{
    int result = -1;
    char *pCur = pBuf;
    char *pEnd = pBuf + bufLen;
    ssize_t subResultLen;
    while (pCur < pEnd) {
        subResultLen = read(fd, pCur, pEnd - pCur);
        if (subResultLen < 0) {
            // perror("read");
            goto EXIT_FUNC;
        } else if (subResultLen == 0) {
            // file is closed
            break;
        }
        pCur += subResultLen;
    }

    result = 0;

EXIT_FUNC:
    if (pResultLen) {
        *pResultLen = pCur - pBuf;
    }

    return result;
}
