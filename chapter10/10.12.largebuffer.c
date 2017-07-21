#include <errno.h>
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

#define buffersize 10000000000

char buf[buffersize] = {0};

int main() {
    struct rlimit limit;
    limit.rlim_cur = buffersize;
    limit.rlim_max = buffersize;
    setrlimit(RLIMIT_FSIZE, &limit);
    signal_intr(SIGALRM, sighandler);

    FILE* file = fopen("test.txt", "wb+");

    alarm(1);

    int written = fwrite(buf, 1, buffersize, file);

    if (ferror(file)) perror("file error");
    printf("Wrote %d bytes, error: %s\n", written, strerror(errno));
    fclose(file);
    exit(0);
}
