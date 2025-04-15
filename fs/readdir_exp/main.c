#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>

int readdirExp(const char *pPath) {
    int result = -1;
    int myErrno;
    DIR *pDir = NULL;
    struct dirent *pEntry;
    char *pEntryPath = NULL;
    size_t entryPathLen = 0;

    printf("sizeof(struct dirent): %zu\n", sizeof(struct dirent));
    printf("sizeof(ino_t): %zu\n", sizeof(ino_t));

    pDir = opendir(pPath);
    if (pDir == NULL) {
        myErrno = errno;
        perror("opendir");
        printf("errno: %d\n", errno);
        goto EXIT_FUNC;
    }

    errno = 0;
    while ((pEntry = readdir(pDir)) != NULL) {
        printf("d_ino: %" PRIdMAX "\n", (intmax_t)pEntry->d_ino);
        printf("d_name: %s\n", pEntry->d_name);
        printf("--\n");
    }
    if (errno != 0) {
        myErrno = errno;
        perror("opendir");
        printf("errno: %d\n", errno);
        goto EXIT_FUNC;
    }

    closedir(pDir);
    pDir = NULL;

    result = 0;

EXIT_FUNC:
    if (pDir != NULL) {
        closedir(pDir);
    }

    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dirName = argv[1];
    if (readdirExp(dirName) != 0) {
        fprintf(stderr, "Error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
