#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>

#ifdef OPEN_MAX
static long openmax = OPEN_MAX;
#else
static long openmax = 0;
#endif

#define OPEN_MAX_GUESS 256

long open_max() {
    if (openmax == 0) errno = 0;
    openmax = sysconf(_SC_OPEN_MAX);
    if (openmax < 0) {
        if (errno == 0 || openmax == LONG_MAX) {
            openmax = OPEN_MAX_GUESS;
        } else {
            fprintf(stderr, "sysconf error for _SC_OPEN_MAX.");
        }
    }
    return openmax;
}

int main() {
    printf("openmax: %ld\n", open_max());
    return 0;
}
