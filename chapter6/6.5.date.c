#include <stdio.h>
#include <time.h>

int main() {
    time_t current = time(NULL);
    struct tm* tm = localtime(&current);
    char buf[40];
    strftime(buf, 40, "%a %b %d %T %Z %Y", tm);
    printf("%s\n", buf);
    return 0;
}
