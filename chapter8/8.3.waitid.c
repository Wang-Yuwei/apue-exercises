#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void wait_and_print_status(pid_t pid) {
    siginfo_t info;
    int result = waitid(P_PID, pid, &info, WEXITED | WSTOPPED);
    if (result == -1 || info.si_pid != pid) {
        fprintf(stderr, "wait error\n");
        exit(0);
    }
    if (info.si_code == CLD_EXITED) {
        printf("normal termination, exit status = %d\n", info.si_status);
    } else if (info.si_code == CLD_KILLED || info.si_code == CLD_DUMPED) {
        printf("abnormal termination, signal number = %d%s\n", info.si_status,
               info.si_code == CLD_DUMPED ? "(core file generated)" : "");
    } else if (info.si_code == CLD_STOPPED) {
        printf("child stopped, signal number = %d\n", info.si_status);
    }
}

pid_t myfork() {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork error");
        exit(0);
    }
    return pid;
}

int main() {
    pid_t pid;

    pid = myfork();
    if (pid == 0) exit(7);
    wait_and_print_status(pid);

    pid = myfork();
    if (pid == 0) abort();
    wait_and_print_status(pid);

    pid = myfork();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdiv-by-zero"
    if (pid == 0) pid /= 0;
#pragma GCC diagnostic pop
    wait_and_print_status(pid);
    return 0;
}
