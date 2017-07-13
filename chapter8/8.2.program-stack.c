#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int create_process() {
    pid_t pid = vfork();
    if (pid < 0) {
        fprintf(stderr, "vfork error");
        exit(0);
    } else if (pid == 0) {
        return 1;
    }
    return 0;
}

int main() {
    int result = create_process();
    printf("result of create process: %d\n", result);
    return 0;
}
