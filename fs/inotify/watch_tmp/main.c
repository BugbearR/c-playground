#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/inotify.h>
#include <limits.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + NAME_MAX + 1))

static void display_event_mask(uint32_t mask) {
    if (mask & IN_ACCESS)        printf("IN_ACCESS ");
    if (mask & IN_ATTRIB)        printf("IN_ATTRIB ");
    if (mask & IN_CLOSE_WRITE)   printf("IN_CLOSE_WRITE ");
    if (mask & IN_CLOSE_NOWRITE) printf("IN_CLOSE_NOWRITE ");
    if (mask & IN_CREATE)        printf("IN_CREATE ");
    if (mask & IN_DELETE)        printf("IN_DELETE ");
    if (mask & IN_DELETE_SELF)   printf("IN_DELETE_SELF ");
    if (mask & IN_MODIFY)        printf("IN_MODIFY ");
    if (mask & IN_MOVE_SELF)     printf("IN_MOVE_SELF ");
    if (mask & IN_MOVED_FROM)    printf("IN_MOVED_FROM ");
    if (mask & IN_MOVED_TO)      printf("IN_MOVED_TO ");
    if (mask & IN_OPEN)          printf("IN_OPEN ");
    if (mask & IN_ISDIR)         printf("IN_ISDIR ");
    printf("\n");
}

int main(int argc, char *argv[])
{
    int fd, wd;
    char buffer[BUF_LEN];

    fd = inotify_init();
    if (fd < 0) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    wd = inotify_add_watch(fd, "/tmp", IN_CREATE);
    if (wd < 0) {
        perror("inotify_add_watch");
        close(fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        int i = 0;
        int length = read(fd, buffer, BUF_LEN);

        if (length < 0) {
            perror("read");
            break;
        }

        while (i < length) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];

            // ファイル作成イベントの場合
            if (event->len && (event->mask & IN_CREATE)) {
                printf("name: %s\n", event->name);
                printf("event type: ");
                display_event_mask(event->mask);

                // ファイルかディレクトリかを表示
                if (event->mask & IN_ISDIR) {
                    printf("object type: directory\n");
                } else {
                    printf("object type: file\n");
                }

                printf("------------------------------\n");
            }

            // 次のイベントへ
            i += EVENT_SIZE + event->len;
        }
    }

    // 監視を終了
    inotify_rm_watch(fd, wd);
    close(fd);

    return EXIT_SUCCESS;
}
