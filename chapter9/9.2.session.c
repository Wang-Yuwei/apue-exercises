#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
        exit(-1);
    } else if (pid == 0) {
        while (getppid() != 1) {
            sleep(1);
        }
        pid = setsid();
        printf("pid: %ld, pgid %ld, sid: %ld\n", (long)getpid(),
               (long)getpgrp(), (long)getsid(0));
        if (open("/dev/tty", O_RDWR) < 0) {
            printf("child has no controlling terminal\n");
        } else {
            printf("child has a controlling terminal\n");
        }
    } else {
        if (open("/dev/tty", O_RDWR) < 0) {
            printf("parent has no controlling terminal\n");
        } else {
            printf("parent has a controlling terminal\n");
        }
    }
    return 0;
}
