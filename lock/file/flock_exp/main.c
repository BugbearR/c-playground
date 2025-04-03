#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <fcntl.h>

int writeExact(int fd, const void *pBuf, size_t length)
{
    int subErrno;
    ssize_t wroteLen;
    size_t pos = 0;
    while (pos < length)
    {
        wroteLen = write(fd, pBuf + pos, length - pos);
        if (wroteLen < 0)
        {
            subErrno = errno;
            if (subErrno == EINTR) {
                continue;
            }

            perror("write");
            return -1;
        }
        pos += wroteLen;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int subResult;
    int subErrno;
    char buf[1024 + 1];
    int pid;
    int fd;

    if (argc < 4)
    {
        fprintf(stderr, "usage: %s path repeat1 repeat2(in lock)\n", argv[0]);
        return EXIT_FAILURE;
    }

    pid = getpid();
    int repeat1 = atoi(argv[2]);
    int repeat2 = atoi(argv[3]);

    fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        perror("open");
        return EXIT_FAILURE;
    }

    int j, i;
    int n = 0;
    for (i = 0; i < repeat1; i++)
    {
        subResult = flock(fd, LOCK_EX);
        if (subResult != 0)
        {
            subErrno = errno;
            if (subErrno == EINTR)
            {
                i--;
                continue;
            }
            perror("flock(fd, LOCK_EX)");
            return EXIT_FAILURE;
        }

        for (j = 0; j < repeat2; j++)
        {
            snprintf(buf, sizeof(buf), "%d\t%d\t%d\n", pid, i, j);
            subResult = writeExact(fd, buf, strlen(buf));
            if (subResult != 0)
            {
                return EXIT_FAILURE;
            }
        }
        subResult = flock(fd, LOCK_UN);
        if (subResult != 0)
        {
            perror("flock(fd, LOCK_UN)");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
