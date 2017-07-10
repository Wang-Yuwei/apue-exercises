#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void closefds(int* fds, int size) {
    for (int i = 0; i < size; ++i) {
        close(fds[i]);
    }
}

int dodup2(int oldfd, int newfd) {
    int index = 0;
    int fds[newfd];
    for (; index < newfd; ++index) {
        fds[index] = dup(oldfd);
        if (fds[index] == newfd) {
            break;
        } else if (fds[index] == -1) {
            closefds(fds, index - 1);
            return -1;
        }
    }
    closefds(fds, index - 1);
    return fds[index];
}

int mydup2(int oldfd, int newfd) {
    int tempfd = dup(oldfd);
    int tablesize = getdtablesize();
    if (tempfd == -1)
        return -1;
    else
        close(tempfd);
    if (oldfd == newfd) return newfd;
    if (newfd < 0 || oldfd >= tablesize) {
        errno = EBADF;
        return -1;
    }
    close(newfd);
    return dodup2(oldfd, newfd);
}

void checkdup2() {
    int oldfds[] = {0, 0, 2, 0, -1, 10, -1, 65536};
    int newfds[] = {0, 2, 2, 30, 2, 20, 65536, 65536};
    int count = sizeof(oldfds) / sizeof(oldfds[0]);
    errno = 0;
    for (int i = 0; i < count; ++i) {
        int correctfd = dup2(oldfds[i], newfds[i]);
        int err = errno;
        errno = 0;
        int myfd = mydup2(oldfds[i], newfds[i]);
        int myerr = errno;
        if (correctfd != myfd || err != myerr) {
            fprintf(stderr, "Incorrect result for oldfd %d, newfd %d.\n",
                    oldfds[i], newfds[i]);
            fprintf(stderr, "Correct result %d, error %s.\n", correctfd,
                    strerror(err));
            fprintf(stderr, "You result %d, error %s.\n", myfd,
                    strerror(myerr));
        } else {
            fprintf(stderr, "Successful test for oldfd %d, new fd %d.\n",
                    oldfds[i], newfds[i]);
        }
        errno = 0;
    }
}

int main() {
    checkdup2();
    return 0;
}
