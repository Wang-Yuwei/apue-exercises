#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void print_error(const char* message) {
    perror(message);
    exit(0);
}

int open_destination(const char* filename) {
    int fd = open(filename, O_WRONLY | O_CREAT, 0600);
    if (fd >= 0) return fd;
    fd = open(filename, O_WRONLY | O_TRUNC);
    return fd;
}

void copy(int src, int dst) {
    off_t offset = 0;
    size_t size_used = 0;
    while ((offset = lseek(src, offset, SEEK_DATA)) >= 0) {
        off_t end = lseek(src, offset, SEEK_HOLE);
        lseek(src, offset, SEEK_SET);
        lseek(dst, offset, SEEK_SET);
        const off_t buffer_size = 1024;
        char buffer[1024];
        for (off_t i = offset; i < end; i += buffer_size) {
            size_t size = end - i < buffer_size ? end - i : buffer_size;
            size_used = read(src, buffer, size);
            if (size_used != size) print_error("Fail to read ");
            size_used = write(dst, buffer, size);
            if (size_used != size) print_error("Fail to write");
        }
        offset = lseek(src, 0, SEEK_CUR);
    }
    return;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source destination.", argv[0]);
        exit(0);
    }
    int srcfd = open(argv[1], O_RDONLY);
    if (srcfd < 0) print_error("Fail to open source ");
    int dstfd = open_destination(argv[2]);
    if (dstfd < 0) print_error("Fail to open destination ");
    copy(srcfd, dstfd);
    close(srcfd);
    close(dstfd);
    return 0;
}
