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

ssize_t recvAsPossible(int fd, void *pBuf, size_t size) {
    ssize_t recvLen;

#if defined MSG_DONTWAIT
RECV_BLOCK:
    recvLen = recv(fd, pBuf, size, MSG_DONTWAIT);
    if (recvLen == -1) {
        int subErrno = errno;
        if (subErrno == EAGAIN) {
            return -1;
        }
        if (subErrno == EINTR) {
            goto RECV_BLOCK;
        }
        perror("recv");
        fprintf(stderr, "errno: %d\n", subErrno);
    }
#else /* MSG_DONTWAIT */
RECV_PEEK_BLOCK:
    recvLen = recv(fd, pBuf, size, MSG_PEEK);
    if (recvLen == -1) {
        int subErrno = errno;
        if (subErrno == EAGAIN || subErrno == EINTR) {
            goto RECV_PEEK_BLOCK;
        }
        perror("recv");
        fprintf(stderr, "errno: %d\n", subErrno);
    }

RECV_BLOCK:
    recvLen = recv(fd, pBuf, recvLen, 0);
    if (recvLen == -1) {
        int subErrno = errno;
        if (subErrno == EAGAIN || subErrno == EINTR) {
            goto RECV_BLOCK;
        }
        perror("recv");
        fprintf(stderr, "errno: %d\n", subErrno);
    }
#endif /* MSG_DONTWAIT */

    return recvLen;
}

ssize_t sendExact(int fd, void *pBuf, size_t size) {
    char *pBufWk = pBuf;
    size_t pos = 0;
    ssize_t sendLen;
    
    do {
        sendLen = send(fd, pBufWk + pos, size - pos, 0);
        if (sendLen == -1) {
            int subErrno = errno;
            if (subErrno == EAGAIN || subErrno == EINTR) {
                continue;
            }
            perror("send");
            fprintf(stderr, "errno: %d\n", subErrno);
            errno = subErrno;
            return -1;
        }
        pos += sendLen;
    } while (pos < size);

    return size;
}

int main(int argc, char *argv[])
{
    int result = EXIT_FAILURE;
    int subResult;
    char *path = NULL;
    char buf[1024];
    char lineBuf[1024];

    if (argc < 2) {
        fprintf(stderr, "usage: %s path\n", argv[0]);
        return EXIT_FAILURE;
    }

    path = argv[1];

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
        fprintf(stderr, "path too long. path: %zu, sun.sun_path: %zu\n", pathLen, sunPathLen);
        goto EXIT_FUNC;
    }
    strncpy(serverAddr.sun_path, path, sizeof(serverAddr.sun_path) - 1);

    subResult = connect(serverFd, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (subResult == -1) {
        int subErrno = errno;
        perror("connect");
        fprintf(stderr, "errno: %d\n", subErrno);
        goto EXIT_FUNC;
    }

    while (fgets(&(lineBuf[0]), sizeof(lineBuf), stdin)) {
        ssize_t recvLen;
        ssize_t sendLen;
        size_t lineBufLen = strlen(lineBuf);
        sendLen = sendExact(serverFd, &(lineBuf[0]), lineBufLen);
        if (sendLen == -1) {
            int subErrno = errno;
            perror("sendExact");
            fprintf(stderr, "errno: %d\n", subErrno);
            break;
        }

RECV_BLOCK:
        recvLen = recvAsPossible(serverFd, buf, sizeof(buf));
        if (recvLen == -1) {
            int subErrno = errno;
            if (subErrno == EAGAIN) {
                usleep(1000);
                goto RECV_BLOCK;
            }
            perror("recvAsPossible");
            fprintf(stderr, "errno: %d\n", subErrno);
            break;
        }
        if (recvLen == 0) {
            printf("[EOF]");
            break;
        }
        fprintBytes(stdout, buf, recvLen);
    }

    result = EXIT_SUCCESS;

EXIT_FUNC:
    if (serverFd != -1) {
        close(serverFd);
    }

    return result;
}
