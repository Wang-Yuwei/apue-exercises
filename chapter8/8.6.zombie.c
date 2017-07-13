#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork error\n");
        exit(-1);
    } else if (pid == 0) {
        exit(0);
    } else {
        printf("child processid: %ld\n", (long)pid);
        system("ps -s");
    }
    return 0;
}
