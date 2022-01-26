#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int subResult;

    if (!system(NULL))
    {
        fprintf(stderr, "system() is not supported.\n");
        return EXIT_FAILURE;
    }

    if (argc < 2) {
        fprintf(stderr, "usage: %s command_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    subResult = system(argv[1]);
    if (WIFEXITED(subResult))
    {
        printf("EXITED\n");
        printf("exit_status: %d\n", WEXITSTATUS(subResult));
    }
    else if (WIFSIGNALED(subResult))
    {
        printf("SIGNALED\n");
        printf("signal_no: %d\n", WTERMSIG(subResult));
#ifdef WCOREDUMP
        printf("coredumped: %d\n", WCOREDUMP(subResult));
#endif
    }
    else
    {
        printf("Unknown status.\n");
        printf("return: %08x\n", subResult);
    }
    return EXIT_SUCCESS;
}
