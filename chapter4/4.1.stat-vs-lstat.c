#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    struct stat buf;
    char* ptr;
    for (int i = 1; i < argc; ++i) {
        printf("%s: ", argv[i]);
        /*
          If we use stat here, the type of a symbolic link will depend on
          the file it points to. If we use lstat, the type of a symbolic link
          will be a "symbolic link".
        */
        if (stat(argv[i], &buf) < 0) {
            fprintf(stderr, "stat error.\n");
            continue;
        }
        if (S_ISREG(buf.st_mode))
            ptr = "regular";
        else if (S_ISDIR(buf.st_mode))
            ptr = "directory";
        else if (S_ISCHR(buf.st_mode))
            ptr = "character special";
        else if (S_ISBLK(buf.st_mode))
            ptr = "block special";
        else if (S_ISFIFO(buf.st_mode))
            ptr = "fifo";
        else if (S_ISLNK(buf.st_mode))
            ptr = "symbolic link";
        else if (S_ISSOCK(buf.st_mode))
            ptr = "socket";
        else
            ptr = "** unknown mode **";
        printf("%s.\n", ptr);
    }
    return 0;
}
