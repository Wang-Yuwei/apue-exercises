#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    sigset_t sigset;

    if (sigprocmask(0, NULL, &sigset) < 0) {
        perror("sigprocmask error");
        exit(0);
    }
    for (int i = 0; i < NSIG; ++i) {
        if (sigismember(&sigset, i)) {
            printf("%s\n", strsignal(i));
        }
    }
    return 0;
}
