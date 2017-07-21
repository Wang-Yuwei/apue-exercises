#include <signal.h>
#include <stdio.h>
#include <string.h>

int sig2str(int signo, char* str) {
    char* signame = strsignal(signo);
    if (signame == NULL) return -1;
    strcpy(str, signame);
    return 0;
}

int main() {
    char buf[40];
    sig2str(SIGINT, buf);
    printf("sig %d: %s\n", SIGINT, buf);
    return 0;
}
