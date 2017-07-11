#include <stdio.h>
#include <stdlib.h>
#include <sys/utsname.h>

int main() {
    struct utsname buf;
    int result = uname(&buf);
    if (result != 0) {
        perror("unable to fetch system info");
        exit(0);
    }
    printf("sysname: %s\n", buf.sysname);
    printf("nodename: %s\n", buf.nodename);
    printf("release: %s\n", buf.release);
    printf("version: %s\n", buf.version);
    printf("machine: %s\n", buf.machine);
    return 0;
}
