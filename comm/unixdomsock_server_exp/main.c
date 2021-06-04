#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <net/if.h>

#define LISTEN_BACK_LOG 10

void fprintBytes(FILE *pFile, const char *pBuf, size_t size) {
    for (size_t i = 0; i < size; i++) {
        if (i > 0) {
            fprintf(pFile, ", ");
        }
        fprintf(pFile, "0x%02hhx", pBuf[i]);
    }
}

void fprintSockaddrUn(FILE *pFile, struct sockaddr_un *pSockaddrUn) {
    fprintf(pFile, "%s", pSockaddrUn->sun_path);
}

void fprintSockaddrIn(FILE *pFile, struct sockaddr_in *pSockaddrIn) {
    char addrBuf[INET_ADDRSTRLEN];
    const char *pAddr = inet_ntop(AF_INET, (const void *)&(pSockaddrIn->sin_addr), &(addrBuf[0]), sizeof(addrBuf));
    if (!pAddr) {
        int subErrno = errno;
        perror("inet_ntop");
        fprintf(stderr, "errno: %d\n", subErrno);
        return;
    }
    fprintf(pFile, "%s:%hu", addrBuf, ntohs(pSockaddrIn->sin_port));
}

void fprintSockaddrIn6(FILE *pFile, struct sockaddr_in6 *pSockaddrIn6) {
    char addrBuf[INET6_ADDRSTRLEN];
    const char *pAddr = inet_ntop(AF_INET6, (const void *)&(pSockaddrIn6->sin6_addr), &(addrBuf[0]), sizeof(addrBuf));
    if (!pAddr) {
        int subErrno = errno;
        perror("inet_ntop");
        fprintf(stderr, "errno: %d\n", subErrno);
        return;
    }
    fprintf(pFile, "%s", addrBuf);
    if (pSockaddrIn6->sin6_scope_id != 0) {
        char ifBuf[IF_NAMESIZE];
        char *pIfBuf = if_indextoname(pSockaddrIn6->sin6_scope_id, &(ifBuf[0]));
        if (!pIfBuf) {
            int subErrno = errno;
            perror("if_indextoname");
            fprintf(stderr, "errno: %d\n", subErrno);
            return;
        }
        fprintf(pFile, "%%%s", ifBuf);
    }
    fprintf(pFile, ":%hu", ntohs(pSockaddrIn6->sin6_port));
}

void fprintSockaddrUnknown(FILE *pFile, struct sockaddr *pSockaddr) {
    fprintf(pFile, "unknown sa_family: 0x%04hx", pSockaddr->sa_family);
    fprintf(pFile, ", sa_data: [");
    fprintBytes(pFile, (char *)pSockaddr->sa_data, sizeof(pSockaddr->sa_data));
    fprintf(pFile, "]");
}

void fprintSockaddr(FILE *pFile, struct sockaddr *pSockaddr) {
    switch (pSockaddr->sa_family) {
    case AF_UNIX:
        fprintSockaddrUn(pFile, (struct sockaddr_un *)pSockaddr);
        break;

    case AF_INET:
        fprintSockaddrIn(pFile, (struct sockaddr_in *)pSockaddr);
        break;

    case AF_INET6:
        fprintSockaddrIn6(pFile, (struct sockaddr_in6 *)pSockaddr);
        break;

    default:
        fprintSockaddrUnknown(pFile, pSockaddr);
    }
}

void childProc(struct sockaddr_un clientAddr, int clientFd) {
    while (1) {
        char buf[1024];
        ssize_t recvLen;
        ssize_t sendLen;
RECV_BLOCK:
        recvLen = recv(clientFd, buf, sizeof(buf), 0);
        if (recvLen == -1) {
            int subErrno = errno;
            perror("recv");
            fprintf(stderr, "errno: %d\n", subErrno);
            if (subErrno == EAGAIN || subErrno == EINTR) {
                goto RECV_BLOCK;
            }
            return;
        }
        if (recvLen == 0) {
            printf("[EOF]");
            return;
        }
        fprintBytes(stdout, buf, recvLen);
SEND_BLOCK:
        sendLen = send(clientFd, buf, recvLen, 0);
        if (sendLen == -1) {
            int subErrno = errno;
            perror("send");
            fprintf(stderr, "errno: %d\n", subErrno);
            if (subErrno == EAGAIN || subErrno == EINTR) {
                goto RECV_BLOCK;
            }
            return;
        }
    }
}

int acceptMain(int serverFd) {
    struct sockaddr_un clientAddr = {0};
    int clientAddrLen = sizeof(clientAddr);
    int clientFd = -1;
    clientFd = accept(serverFd, (struct sockaddr *)&clientAddr, &clientAddrLen);
    if (clientFd == -1) {
        int subErrno = errno;
        perror("accept");
        fprintf(stderr, "errno: %d\n", subErrno);
        goto EXIT_FUNC;
    }

    pid_t pid = fork();
    if (pid == -1) {
        int subErrno = errno;
        perror("fork");
        fprintf(stderr, "errno: %d\n", subErrno);
        goto EXIT_FUNC;
    }

    if (pid == 0) {
        close(serverFd);
        childProc(clientAddr, clientFd);
        exit(0);
    }

    close(clientFd);
    clientFd = -1;

EXIT_FUNC:
    if (clientFd != -1) {
        close(clientFd);
    }
}

int main(int argc, char *argv[])
{
    int result = EXIT_FAILURE;
    char *path = NULL;
    int subResult;
    if (argc < 2) {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    path = argv[1];

    subResult = unlink(path);
    if (subResult != 0) {
        int subErrno = errno;
        if (subErrno != ENOENT) {
            perror("unlink");
            fprintf(stderr, "errno: %d\n", subErrno);
            return EXIT_FAILURE;
        }
    }

    int serverFd = -1;
    serverFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (serverFd == -1) {
        int subErrno = errno;
        perror("socket");
        fprintf(stderr, "errno: %d\n", subErrno);
        goto EXIT_FUNC;
    }

    struct sockaddr_un serverAddr = {0};
    serverAddr.sun_family = AF_UNIX;
    size_t pathLen = strlen(path);
    size_t sunPathLen = sizeof(serverAddr.sun_path) - 1; 
    if (pathLen > sunPathLen) {
        fprintf(stderr, "path too long. path: %zu,  sun.sun_path: %zu\n", pathLen, sunPathLen);
        goto EXIT_FUNC;
    }
    strncpy(serverAddr.sun_path, path, sizeof(serverAddr.sun_path) - 1);

    subResult = bind(serverFd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (subResult == -1) {
        int subErrno = errno;
        perror("bind");
        fprintf(stderr, "errno: %d\n", subErrno);
        goto EXIT_FUNC;
    }

    subResult = listen(serverFd, LISTEN_BACK_LOG);
    if (subResult == -1) {
        int subErrno = errno;
        perror("listen");
        fprintf(stderr, "errno: %d\n", subErrno);
        goto EXIT_FUNC;
    }

    while (1) {
        acceptMain(serverFd);
    }

    // result = EXIT_SUCCESS;

EXIT_FUNC:
    if (serverFd != -1) {
        close(serverFd);
    }

    return result;
}
