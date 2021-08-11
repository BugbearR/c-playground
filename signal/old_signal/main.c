#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

typedef void (*my_sighandler_t)(int);

volatile sig_atomic_t g_sigNo = 0;

void signalHandler(int sigNo)
{
    g_sigNo = sigNo;
}

int main(void)
{
    int result = EXIT_FAILURE;
    int subResult;
    int subErrno;
    int count;
    my_sighandler_t oldHandler;

    oldHandler = signal(SIGINT, signalHandler);
    if (oldHandler == SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    oldHandler = signal(SIGUSR1, signalHandler);
    if (oldHandler == SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }

    for (count = 0; ; count++)
    {
        printf("%d\n", count);
        printf("sleep\n");
        errno = 0;
        subResult = sleep(2);
        if (errno != 0) {
            subErrno = errno;
            if (subErrno == EINTR)
            {
                printf("EINTR in sleep.\n");
                printf("sigNo:%d\n", (int)g_sigNo);
                g_sigNo = 0;
            }
            else
            {
                perror("sleep");
                exit(EXIT_FAILURE);
            }
        }
        printf("loop\n");
    }

EXIT_FUNC:

    return result;
}
