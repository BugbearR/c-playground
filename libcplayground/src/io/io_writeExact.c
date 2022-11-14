#include <cplayground/io.h>

#include <unistd.h>

int cplayground_io_writeExact(int fd, const char *pBuf, size_t bufLen, size_t *pResultLen)
{
    int result = -1;
    const char *pCur = pBuf;
    const char *pEnd = pBuf + bufLen;
    ssize_t subResultLen;
    while (pCur < pEnd) {
        subResultLen = write(fd, pCur, pEnd - pCur);
        if (subResultLen < 0) {
            // perror("write");
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
        pResultLen = pCur - pBuf;
    }

    return result;
}
