#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    DIR* dir = opendir("/");
    int fd = dirfd(dir);
    printf("close on exec flag: %s\n",
           fcntl(fd, F_GETFD) & FD_CLOEXEC ? "true" : "false");
    closedir(dir);

    fd = open("/", O_RDONLY);
    printf("close on exec flag: %s\n",
           fcntl(fd, F_GETFD) & FD_CLOEXEC ? "true" : "false");
    close(fd);
    return 0;
}
