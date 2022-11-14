#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

extern char **environ;

int main(int argc, char *argv[])
{
    int subResult = 0;
    int myErrno;

    if (argc < 2) {
        fprintf(stderr, "usage: %s exe_path [args ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    char **pSubArgv = malloc(sizeof(char *) * argc);
    memcpy(pSubArgv, &(argv[1]), sizeof(char *) * (argc - 1));
    pSubArgv[argc - 1] = NULL;

    subResult = execve(argv[1], pSubArgv, environ);
    if (subResult != 0) {
        myErrno = errno;
        perror("execve");
        printf("errno: %d, strerror: %s\n", myErrno, strerror(myErrno));
    }

    return EXIT_FAILURE;
}
