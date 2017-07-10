#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char buf1[] = "abcdefghij";
    const char buf2[] = "ABCDEFGHIJ";

    int fd = open("file.hole", O_WRONLY | O_CREAT, 0600);
    if (fd < 0) {
        perror("Fail to open file: ");
    }
    if (write(fd, buf1, 10) != 10) {
        perror("Fail to write buf1: ");
    }
    if (lseek(fd, 16284, SEEK_SET) == -1) {
        perror("Fail to seek: ");
    }
    if (write(fd, buf2, 10) != 10) {
        perror("Fail to write buf2: ");
    }
    return 0;
}
