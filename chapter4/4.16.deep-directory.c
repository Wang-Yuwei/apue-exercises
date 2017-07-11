#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    const char pathname[] =
        "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz"
        "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
    int namelength = strlen(pathname);
    int pathmax = PATH_MAX;

    printf("PATH MAX: %d.\n", pathmax);
    for (int i = 0; i <= pathmax / namelength + 1; ++i) {
        int result = mkdir(pathname, 0770);
        if (result != 0) {
            perror("unable to create directory");
            exit(0);
        }
        chdir(pathname);
    }
    char* fullpath = malloc(pathmax * 3);
    char* result = getcwd(fullpath, pathmax * 3);
    if (result == NULL) {
        printf("Unable to getcwd()\n");
    } else {
        printf("Path length: %zu\n", strlen(fullpath));
        printf("Current directory: %s\n", fullpath);
    }
    system("pwd");
    return 0;
}
