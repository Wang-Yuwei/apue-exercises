#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    const char path[] = "/dev/fd/1";
    const char content[] = "test\n";
    int result = unlink(path);
    if (result != 0) {
        printf("unable to unlink file.\n");
    }
    int fd = -1;
    if ((fd = open(path, O_WRONLY | O_CREAT, 0666)) < 0) {
        perror("unable to create file");
    } else {
        write(fd, content, strlen(content));
    }
    return 0;
}
