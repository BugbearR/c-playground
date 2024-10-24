#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    int start = 0;
    int length = 0;
    struct flock lock;
    char buf[32];
    int ret;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file> [start] [length]\n", argv[0]);
        exit(1);
    }

    if (argc > 2) {
        start = atoi(argv[2]);
    }

    if (argc > 3) {
        length = atoi(argv[3]);
    }

    fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    printf("Opened\n");

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = length;
    ret = fcntl(fd, F_SETLKW, &lock);
    if (ret < 0) {
        perror("fcntl");
        exit(1);
    }

    printf("Locked\n");

    sleep(10);

    lock.l_type = F_UNLCK;
    ret = fcntl(fd, F_SETLK, &lock);
    if (ret < 0) {
        perror("fcntl");
        exit(1);
    }

    printf("Unlocked\n");

    close(fd);

    return 0;
}
