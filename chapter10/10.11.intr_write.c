#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <unistd.h>

typedef void sig_func_t(int);

sig_func_t* signal_intr(int signo, sig_func_t* func) {
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
    if (sigaction(signo, &act, &oact) < 0) return SIG_ERR;
    return oact.sa_handler;
}

void sighandler(int signo) {
    printf("Caught %d, %s\n", signo, strsignal(signo));
}

int main() {
    struct rlimit limit;
    limit.rlim_cur = 1024;
    limit.rlim_max = 10000;
    setrlimit(RLIMIT_FSIZE, &limit);
    signal_intr(SIGXFSZ, sighandler);

    static const int buffersize = 100;
    char buf[buffersize];
    int n, written;
    while ((n = read(STDIN_FILENO, buf, buffersize)) > 0) {
        if ((written = write(STDOUT_FILENO, buf, buffersize)) != n) {
            fprintf(stderr, "Wrote %d bytes\n", written);
            exit(-1);
        }
    }
    exit(0);
}
