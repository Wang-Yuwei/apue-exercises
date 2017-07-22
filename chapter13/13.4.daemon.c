#include <syslog.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void err_quit(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(-1);
}

void daemonize(const char* cmd) {
    int fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    umask(0);

    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
        err_quit("%s: cannot get file limit\n", cmd);

    pid = fork();
    if (pid < 0)
        err_quit("%s: cannot fork\n", cmd);
    else if (pid != 0)
        exit(0);

    setsid();

    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        err_quit("%s: cannot ignore SIGHUP\n", cmd);
    pid = fork();
    if (pid < 0)
        err_quit("%s: cannot fork\n", cmd);

    if (chdir("/") < 0)
        err_quit("%s: cannot chdir to /\n", cmd);

    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (size_t i = 0; i < rl.rlim_max; ++i) close(i);
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
        syslog(LOG_ERR, "unexpected file descriptor %d %d %d", fd0, fd1, fd2);
        exit(1);
    }
}

int main(int argc, char** argv) {
    if (argc != 1) {
        abort();
    }
    daemonize(argv[0]);
    FILE* fp = fopen("/home/wyw/loginname.txt", "w+");
    char buf[1024];
    int error = getlogin_r(buf, 1024);
    if (error != 0) {
        fprintf(fp, "%s\n", strerror(error));
    }
    fclose(fp);
    return 0;
}
