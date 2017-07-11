#include <stdio.h>

void mysetbuf(FILE* stream, char* buf) {
    // copied from the man page.
    setvbuf(stream, buf, buf ? _IOFBF : _IONBF, BUFSIZ);
}

int main() { return 0; }
