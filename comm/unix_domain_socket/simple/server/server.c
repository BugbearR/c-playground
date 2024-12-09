// #define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static volatile sig_atomic_t s_isStopRequested = 0;

void mySignalHandler(int sigNo, siginfo_t *pInfo, void *pCtx)
{
    s_isStopRequested = 1;
}

int listenUnixDomainSocket(const char *path)
{
    int serverFd;
    struct sockaddr_un serverAddr;

    if (strlen(path) >= sizeof(serverAddr.sun_path)) {
        fprintf(stderr, "path too long. path: %zu, sun.sun_path: %zu\n", strlen(path), sizeof(serverAddr.sun_path));
        return -1;
    }

    serverFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverFd == -1) {
        perror("socket");
        return -1;
    }

    unlink(path);

    serverAddr.sun_family = AF_UNIX;
    strncpy(serverAddr.sun_path, path, sizeof(serverAddr.sun_path) - 1);

    if (bind(serverFd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(serverFd, 5) == -1) {
        perror("listen");
        return -1;
    }

    return serverFd;
}

int main(int argc, char *argv[])
{
    int result = EXIT_FAILURE;
    const char *path;
    struct sigaction sa = {0};
    int serverFd;
    struct sockaddr_un serverAddr;

    if (argc < 2) {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    path = argv[1];

    sa.sa_sigaction = mySignalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGINT, &sa, NULL) == -1)
    {
        perror("sigaction");
        goto EXIT_FUNC;
    }

    if (sigaction(SIGTERM, &sa, NULL) == -1)
    {
        perror("sigaction");
        goto EXIT_FUNC;
    }

    serverFd = listenUnixDomainSocket(path);
    if (serverFd == -1) {
        goto EXIT_FUNC;
    }

    int clientFd = accept(serverFd, NULL, NULL);
    if (clientFd == -1) {
        perror("accept");
        goto EXIT_FUNC;
    }

    char buf[1024];
    while (!s_isStopRequested) {
        ssize_t recvLen = 0;
        recvLen = recv(clientFd, buf, sizeof(buf) - 1, 0);
        if (recvLen == -1) {
            if (errno == EINTR) {
                continue;
            }
            perror("recv");
            goto EXIT_FUNC;
        } else if (recvLen == 0) {
            printf("client closed\n");
            break;
        }

        buf[recvLen] = '\0';
        printf("received: (%zd)\"%s\"\n", recvLen, buf);

        ssize_t sendLen;
        sendLen = send(clientFd, buf, recvLen, 0);
        if (sendLen == -1) {
            perror("send");
            goto EXIT_FUNC;
        }
        printf("send: (%zu)\"%s\"\n", recvLen, buf);
    }

    result = EXIT_SUCCESS;

EXIT_FUNC:
    if (serverFd != -1) {
        close(serverFd);
    }
    if (path) {
        unlink(path);
    }

    return result;
}
