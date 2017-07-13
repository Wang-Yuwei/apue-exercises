#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int globvar = 6;

int main() {
    int var;
    pid_t pid;
    var = 88;
    printf("before vfork\n");
    pid = vfork();
    if (pid < 0) {
        fprintf(stderr, "vfork error");
        exit(0);
    } else if (pid == 0) {
        ++globvar;
        ++var;
        exit(0);
    } else {
        printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar,
               var);
        exit(0);
    }
}
