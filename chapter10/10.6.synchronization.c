#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static volatile sig_atomic_t sigflag = 0;
static sigset_t newmask, oldmask, zeromask;

static void sig_usr(int signo) {
    (void)signo;
    sigflag = 1;
}

void TELL_WAIT() {
    if (signal(SIGUSR1, sig_usr) == SIG_ERR) perror("signal(SIGUSR1) error");
    if (signal(SIGUSR2, sig_usr) == SIG_ERR) perror("signal(SIGUSR2) error");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        perror("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid) { kill(pid, SIGUSR2); }

void WAIT_PARENT() {
    while (sigflag == 0) sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

void TELL_CHILD(pid_t pid) { kill(pid, SIGUSR1); }

void WAIT_CHILD() {
    while (sigflag == 0) sigsuspend(&zeromask);
    sigflag = 0;
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        perror("SIG_SETMASK error");
}

int main() {
    FILE* file = fopen("test.txt", "w+");
    int x = 0;
    fprintf(file, "parent write %d\n", x);
    fflush(file);
    TELL_WAIT();

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork error");
    } else if (pid > 0) {
        WAIT_CHILD();
        for (int i = 0; i < 10; ++i) {
            ++x;
            fprintf(file, "parent write %d\n", x);
            fflush(file);
            sleep(1);
            TELL_CHILD(pid);
            if (i < 9) WAIT_CHILD();
        }
    } else {
        pid = getppid();
        for (int i = 0; i < 10; ++i) {
            fprintf(file, "child write %d\n", x);
            fflush(file);
            ++x;
            TELL_PARENT(pid);
            WAIT_PARENT();
        }
        exit(0);
    }
    fclose(file);
}
