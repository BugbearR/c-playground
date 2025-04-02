#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/limits.h>

int main(int argc, char *argv[])
{
    int myerrno;

    FILE *pFile = NULL;
    int fd = -1;
    char procpath[PATH_MAX];
    char filepath[PATH_MAX];
    char buf[1000];

    pFile = tmpfile();
    if (pFile == NULL) {
        myerrno = errno;
        perror("tmpfile");
        printf("errno = %d\n", myerrno);
        return EXIT_FAILURE;
    }

    // printf("tmpfile %p\n", pFile);

    fprintf(pFile, "Hello, World! by fprintf\n");

    fflush(pFile); // flush the buffer to ensure data is written to the file

    fseek(pFile, 0, SEEK_SET); // reset the file pointer to the beginning

    if (fgets(buf, sizeof(buf), pFile) == NULL) {
        myerrno = errno;
        perror("fgets");
        printf("errno = %d\n", myerrno);
        fclose(pFile);
        return EXIT_FAILURE;
    }
    printf("fgets: %s\n", buf);

    fclose(pFile);

    return EXIT_SUCCESS;
}
