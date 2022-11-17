#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int parentProc(pid_t childPid, int count, int sleepTimeUs)
{
    int i;
    int childStatus;

    printf("child pid: %d\n", childPid);

    for (i = 0; i < count; i++)
    {
        printf("parent: %d\n", i);
        usleep(sleepTimeUs);
    }
    printf("wait pid: %d\n", childPid);
//    pid_t pid = waitpid(childPid, &childStatus, WEXITED);
    pid_t pid = waitpid(childPid, &childStatus, 0);
    if (pid == -1)
    {
        perror("waitpid");
        return EXIT_FAILURE;
    }
    printf("wait pid end: %d\n", childStatus);
    if (WIFEXITED(childStatus))
    {
        int childEsitStatus = WEXITSTATUS(childStatus);
        printf("child exit status: %d\n", childEsitStatus);
    }
    else if (WIFSIGNALED(childStatus))
    {
        int childTermSignal = WTERMSIG(childStatus);
        printf("child signaled: %d\n", childTermSignal);
    }
    else {
        printf("unknown child sstatus\n");
    }
    return EXIT_SUCCESS;
}

int childProc(int count, int sleepTimeUs, int exitStatus)
{
    int i;
    for (i = 0; i < count; i++)
    {
        printf("child: %d\n", i);
        usleep(sleepTimeUs);
    }
    return exitStatus;
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "usage: %s parentCount parentSleepTimeUs childCount childSleepTimeUs childExitStatus\n", argv[0]);
        fprintf(stderr, "sample: %s 10 1000000 10 500000 0\n", argv[0]);
        return EXIT_FAILURE;
    }

    int parentCount = atoi(argv[1]);
    int parentSleepTimeUs = atoi(argv[2]);
    int childCount = atoi(argv[3]);
    int childSleepTimeUs = atoi(argv[4]);
    int childExitStatus = atoi(argv[5]);

    pid_t childPid = fork();
    if (childPid > 0) {
        return parentProc(childPid, parentCount, parentSleepTimeUs);
    }
    else if (childPid == 0) {
        return childProc(childCount, childSleepTimeUs, childExitStatus);
    }
    else {
        perror("fork");

        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
