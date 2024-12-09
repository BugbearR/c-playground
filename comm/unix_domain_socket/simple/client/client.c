// #define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int connect_to_server(const char *path)
{
    int fd = -1;
    struct sockaddr_un addr = {0};

    addr.sun_family = AF_UNIX;
    if (strlen(path) >= sizeof(addr.sun_path)) {
        fprintf(stderr, "path too long. path: %zu, sun.sun_path: %zu\n", strlen(path), sizeof(addr.sun_path));
        return -1;
    }

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("socket");
        return -1;
    }

    strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("connect");
        close(fd);
        return -1;
    }

    return fd;
}

int main(int argc, char *argv[])
{
    int result = EXIT_FAILURE;
    int fd = -1;
    const char *path;
    const char *msg;
    size_t msgLen;
    char buf[1024];

    if (argc < 3) {
        fprintf(stderr, "usage: %s path msg\n", argv[0]);
        return EXIT_FAILURE;
    }

    path = argv[1];
    msg = argv[2];

    fd = connect_to_server(path);
    if (fd == -1) {
        return EXIT_FAILURE;
    }

    while (1) {
        msgLen = strlen(msg);
        ssize_t sendLen = 0;
        sendLen = send(fd, msg, msgLen, 0);
        if (sendLen == -1) {
            perror("send");
            close(fd);
            return EXIT_FAILURE;
        }
        printf("send: (%zu)\"%s\"\n", msgLen, msg);

        ssize_t recvLen = 0;
        recvLen = recv(fd, buf, sizeof(buf) - 1, 0);
        if (recvLen == -1) {
            perror("recv");
            goto EXIT_FUNC;
        } else if (recvLen == 0) {
            fprintf(stderr, "server closed\n");
            goto EXIT_FUNC;
        }

        printf("received: (%zd)\"%s\"\n", recvLen, buf);
        sleep(3);
    }

    result = EXIT_SUCCESS;

EXIT_FUNC:

    if (fd != -1) {
        close(fd);
    }

    return result;
}
