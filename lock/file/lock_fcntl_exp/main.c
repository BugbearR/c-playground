#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd;
    int repeatCount = 1;
    int start = 0;
    int length = 0;
    struct flock lock;
    char *buf;
    int ret;
    int i;
    int j;
    int k;
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file> [repeatCount] [start] [length]\n", argv[0]);
        exit(1);
    }

    if (argc > 2) {
        repeatCount = atoi(argv[2]);
    }

    if (argc > 3) {
        start = atoi(argv[3]);
    }

    if (argc > 4) {
        length = atoi(argv[4]);
    }

    pid = getpid();

    buf = malloc(length);
    if (buf == NULL) {
        perror("malloc");
        exit(1);
    }

    fd = open(argv[1], O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    printf("Opened\n");

    for (k = 0; k < repeatCount; k++) {
        lock.l_type = F_WRLCK;
        lock.l_whence = SEEK_SET;
        lock.l_start = start;
        lock.l_len = length;
        ret = fcntl(fd, F_SETLKW, &lock);
        if (ret < 0) {
            perror("fcntl");
            exit(1);
        }

        printf("pid: %d, Locked\n", pid);

        for (j = 0; j < 3; j++) {
            off_t newOff = lseek(fd, start, SEEK_SET);
            if (newOff < 0) {
                perror("lseek");
                exit(1);
            }

            ret = read(fd, buf, length);
            if (ret < 0) {
                perror("read");
                exit(1);
            }
            printf("pid: %d, read buf:[%.*s]\n", pid, length, buf);

            for (i = 0; i < length; i++) {
                buf[i] = 'a' + ((i + j + k + pid) % 26);
            }

            printf("pid: %d, write buf:[%.*s]\n", pid, length, buf);
            newOff = lseek(fd, start, SEEK_SET);
            if (newOff < 0) {
                perror("lseek");
                exit(1);
            }
            ret = write(fd, buf, length);
            if (ret < 0) {
                perror("write");
                exit(1);
            }
            sleep(1);
        }

        lock.l_type = F_UNLCK;
        ret = fcntl(fd, F_SETLK, &lock);
        if (ret < 0) {
            perror("fcntl");
            exit(1);
        }

        printf("pid: %d, Unlocked\n", pid);

        sleep(1);
    }

    close(fd);

    return 0;
}
