#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int myerrno;
    int fd = -1;
    char buf[] = "/tmp/mytempfileXXXXXX";
    char data[1000];

    fd = mkstemp(buf);
    if (fd == -1) {
        myerrno = errno;
        perror("mkstemp");
        printf("errno = %d\n", myerrno);
        return EXIT_FAILURE;
    }
    printf("Temporary file created: %s\n", buf);

    char sample[] = "Hello, World! by write\n";
    write(fd, sample, strlen(sample));
    lseek(fd, 0, SEEK_SET); // reset the file pointer to the beginning
    read(fd, data, sizeof(data));
    printf("Read from file: %s\n", data);

    close(fd);
    printf("File descriptor closed.\n");

    // this temporary file won't be deleted automatically, so we'll delete it here.
    unlink(buf);
    printf("File deleted.\n");

    return EXIT_SUCCESS;
}
