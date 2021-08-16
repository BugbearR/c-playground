#define _POSIX_C_SOURCE 199309L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


volatile sig_atomic_t g_sigNo;
volatile sig_atomic_t g_serial;

void mySignalHandler(int sigNo, siginfo_t *pInfo, void *pCtx)
{
    char fileName[32];
    char buf[128];
    int fd = -1;
    struct timespec ts;

    g_sigNo = sigNo;
    clock_gettime(CLOCK_REALTIME, &ts);
    snprintf(fileName, sizeof(buf), "signal_%010d", (int)g_serial);
    g_serial++;
    fd = open(fileName, O_CREAT | O_WRONLY, S_IRUSR);
    snprintf(buf, sizeof(buf), "%" PRIdMAX ".%09ld\n", (intmax_t)ts.tv_sec, ts.tv_nsec);
    write(fd, buf, strlen(buf));
EXIT_FUNC:
    if (fd != -1) {
        close(fd);
    }
}

int main(void)
{
    int result = EXIT_FAILURE;
    int subResult;
    int subErrno;
    int count;
    int i;
    int s;
    struct sigaction sa = {0};
    // struct sigaction oldSa1 = {0};
    // struct sigaction oldSa2 = {0};

    sa.sa_sigaction = mySignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

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
                printf("EINTR in sleep.\n");
                printf("g_sigNo:%d\n", (int)g_sigNo);
            }
        }
        printf("busy loop\n");
        s = 0;
        for (i = 0; i < 1000000000; i++)
        {
            s += rand();
        }
        printf("s:%d\n", s);
        printf("busy loop end\n");
    }

EXIT_FUNC:

    return result;
}
