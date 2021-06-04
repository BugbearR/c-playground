#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t g_sigNo;

void sigHandler(int sigNo) {
    g_sigNo = (sig_atomic_t)sigNo;
}

int main(void)
{
    int subResult;
    int subErrno;
    int i;
    void (*orgHandler)(int);

    for (i = 1; i <= 64; i++) {
        if (i == SIGKILL || i == SIGSTOP || i == 32 || i == 33) {
            continue;
        }
        orgHandler = signal(i, sigHandler);
        if (orgHandler == SIG_ERR) {
            subErrno = errno;
            perror("signal");
            fprintf(stderr, "errno:%d\n", subErrno);
            fprintf(stderr, "sigNo:%d\n", i);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    subResult = sleep(30);
    if (subResult > 0) {
        perror("sleep");
    }
    subErrno = errno;
    printf("result:%d, errno:%d, g_sigNo:%d\n", subResult, subErrno, g_sigNo);
    return EXIT_SUCCESS;
}
