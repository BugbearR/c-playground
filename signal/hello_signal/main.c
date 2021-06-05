#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result = EXIT_FAILURE;
    int subResult;
    int subErrno;
    int count;

    for (count = 0; ; count++)
    {
        printf("%d\n", count);
        printf("sleep\n");
        subResult = sleep(2);
        if (subResult < 0)
        {
            subErrno = errno;
            perror("sleep");
        }
        if (subResult > 0)
        {
            subErrno = errno;
            if (subErrno == EINTR)
            {
                printf("EINTR in sleep.");
            }
        }
        printf("busy loop\n");
    }

EXIT_FUNC:

    return result;
}
