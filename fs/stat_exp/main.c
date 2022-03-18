#define _POSIX_SOURCE
#define _POSIX_C_SOURCE 200809L

#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int subResult;
    struct stat statBuf;

    if (argc < 2)
    {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    subResult = stat(argv[1], &statBuf);
    if (subResult != 0)
    {
        int subErrno = errno;
        perror("rename");
        fprintf(stderr, "errno: %d\n", subErrno);
        return EXIT_FAILURE;
    }

    printf("sizeof_uintmax_t: %zu\n", sizeof(uintmax_t));
    printf("sizeof_dev_t: %zu\n", sizeof(dev_t));
    printf("st_dev: %"PRIdMAX"\n", (uintmax_t)statBuf.st_dev);
    printf("sizeof_ino_t: %zu\n", sizeof(ino_t));
    printf("st_ino: %"PRIdMAX"\n", (uintmax_t)statBuf.st_ino);
    printf("sizeof_mode_t: %zu\n", sizeof(mode_t));
    printf("st_mode: %08x\n", statBuf.st_mode);
    printf("sizeof_nlink_t: %zu\n", sizeof(nlink_t));
    printf("st_nlink: %"PRIdMAX"\n", (uintmax_t)statBuf.st_nlink);
    printf("sizeof_uid_t: %zu\n", sizeof(uid_t));
    printf("st_uid: %"PRIdMAX"\n", (uintmax_t)statBuf.st_uid);
    printf("sizeof_gid_t: %zu\n", sizeof(gid_t));
    printf("st_gid: %"PRIdMAX"\n", (uintmax_t)statBuf.st_gid);
    printf("st_rdev: %"PRIdMAX"\n", (uintmax_t)statBuf.st_rdev);
    printf("sizeof_off_t: %zu\n", sizeof(off_t));
    printf("st_size: %"PRIdMAX"\n", (uintmax_t)statBuf.st_size);
    printf("sizeof_blksize_t: %zu\n", sizeof(blksize_t));
    printf("st_blksize: %"PRIdMAX"\n", (uintmax_t)statBuf.st_blksize);
    printf("sizeof_blkcnt_t: %zu\n", sizeof(blkcnt_t));
    printf("st_blocks: %"PRIdMAX"\n", (uintmax_t)statBuf.st_blocks);
    printf("st_atim: \"");
    cplayground_printTimespecLocal(&(statBuf.st_atim));
    printf("\"\n");
    printf("st_mtim: \"");
    cplayground_printTimespecLocal(&(statBuf.st_mtim));
    printf("\"\n");
    printf("st_ctim: \"");
    cplayground_printTimespecLocal(&(statBuf.st_ctim));
    printf("\"\n");
    return EXIT_SUCCESS;
};
