#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

struct foo {
    int a, b, c, d;
};

void printfoo(const char* s, const struct foo* fp) {
    printf("%s", s);
    printf(" structure at %p\n", fp);
    printf(" foo.a = %d\n", fp->a);
    printf(" foo.b = %d\n", fp->b);
    printf(" foo.c = %d\n", fp->c);
    printf(" foo.d = %d\n", fp->d);
}

void* thr_fnl(void* arg) {
    (void)arg;
    printf("thread 1: ID is %lu\n", (unsigned long)pthread_self());
    struct foo* fp = malloc(sizeof(struct foo));
    fp->a = 1;
    fp->b = 2;
    fp->c = 3;
    fp->d = 4;
    printfoo("thread 1:\n", fp);
    pthread_exit((void*)fp);
}

void* thr_fn2(void* arg) {
    (void)arg;
    printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
    pthread_exit((void*)NULL);
}

void exit_error(const char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main() {
    int err;
    pthread_t tid1, tid2;
    struct foo* fp;
    err = pthread_create(&tid1, NULL, thr_fnl, NULL);
    if (err != 0) exit_error("cannot create thread 1");
    err = pthread_join(tid1, (void*)&fp);
    if (err != 0) exit_error("cannot join thread 1");
    sleep(1);
    printf("parent staring second thread\n");
    err = pthread_create(&tid2, NULL, thr_fn2, NULL);
    if (err != 0) exit_error("cannot create thread 2");
    sleep(1);
    printfoo("parent:\n", fp);
    free(fp);
    return 0;
}
