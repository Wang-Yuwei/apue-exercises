#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

typedef int my_func_t(const char*, const struct stat*, int);

static my_func_t myfunc;
static int myftw(char*, my_func_t*);
static int dopath(my_func_t*);
static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock;

void error_quit(const char* message) {
    fputs(message, stderr);
    exit(0);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        error_quit("Usage: ftw <starting-pathname>.");
    }
    struct timeval start, end;
    gettimeofday(&start, NULL);
    myftw(argv[1], myfunc);
    gettimeofday(&end, NULL);

    printf("Regular files  = %7ld\n", nreg);
    printf("Directories    = %7ld\n", ndir);
    printf("Block special  = %7ld\n", nblk);
    printf("Char special   = %7ld\n", nchr);
    printf("FIFOs          = %7ld\n", nfifo);
    printf("symbolic links = %7ld\n", nslink);
    printf("sockets        = %7ld\n", nsock);
    printf("Time used: %lfs\n",
           end.tv_sec - start.tv_sec +
               (double)(end.tv_usec - start.tv_usec) / 1000000.0);
    return 0;
}

#define FTW_F 1
#define FTW_D 2
#define FTW_DNR 3
#define FTW_NS 4

static char* fullpath;
static size_t pathlen;

char* path_alloc(size_t* pathlen) {
    *pathlen = PATH_MAX;
    return malloc(PATH_MAX + 1);
}

static int myftw(char* pathname, my_func_t* func) {
    fullpath = path_alloc(&pathlen);
    if (pathlen <= strlen(pathname)) {
        pathlen = strlen(pathname) * 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            error_quit("realloc failed");
    }
    strcpy(fullpath, pathname);
    return (dopath(func));
}

static int dopath(my_func_t* func) {
    struct stat buf;
    struct dirent* dirp;
    DIR* dp;
    int ret, n;
    if (lstat(fullpath, &buf) < 0) return (func(fullpath, &buf, FTW_NS));
    if (S_ISDIR(buf.st_mode) == 0) return (func(fullpath, &buf, FTW_F));
    if ((ret = func(fullpath, &buf, FTW_D)) != 0) return ret;
    n = strlen(fullpath);
    if (n + NAME_MAX + 2 > (int)pathlen) {
        pathlen *= 2;
        if ((fullpath = realloc(fullpath, pathlen)) == NULL)
            error_quit("realloc failed");
    }
    fullpath[n++] = '/';
    fullpath[n] = 0;
    if ((dp = opendir(fullpath)) == NULL)
        return (func(fullpath, &buf, FTW_DNR));
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        strcpy(&fullpath[n], dirp->d_name);
        if ((ret = dopath(func)) != 0) break;
    }
    fullpath[n - 1] = 0;
    if (closedir(dp) < 0) error_quit("Cannot close directory");
    return ret;
}

static int myfunc(const char* pathname, const struct stat* buf, int type) {
    (void)pathname;
    switch (type) {
    case FTW_F:
        switch (buf->st_mode & S_IFMT) {
        case S_IFREG:
            ++nreg;
            break;
        case S_IFBLK:
            ++nblk;
            break;
        case S_IFCHR:
            ++nchr;
            break;
        case S_IFIFO:
            ++nfifo;
            break;
        case S_IFLNK:
            ++nslink;
            break;
        case S_IFSOCK:
            ++nsock;
            break;
        case S_IFDIR:
            error_quit("cannot use S_IFDIR");
        }
        break;
    case FTW_D:
        ++ndir;
        break;
    case FTW_DNR:
        error_quit("cannot read directory");
        break;
    case FTW_NS:
        error_quit("stat error");
        break;
    default:
        error_quit("unknown type");
        break;
    }
    return 0;
}
