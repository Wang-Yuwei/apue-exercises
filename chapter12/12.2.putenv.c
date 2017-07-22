#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int putenv_r(char* string);

extern char** environ;

pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;
int is_first_put = 0;

int main() {
    int ret = putenv_r("key1=value");
    printf("return %d: key1=%s\n", ret, getenv("key1"));
    ret = putenv_r("key2=value2");
    printf("return %d: key2=%s\n", ret, getenv("key2"));
    return 0;
}

int putenv_r(char* string) {
    sigset_t block, old;
    sigfillset(&block);
    pthread_sigmask(SIG_BLOCK, &block, &old);
    int len = strlen(string);
    int keylen = 0;
    while (keylen < len && string[keylen] != '=') keylen++;
    if (keylen == 0) {
        errno = EINVAL;
        pthread_sigmask(SIG_SETMASK, &old, NULL);
        return -1;
    }
    pthread_mutex_lock(&env_mutex);
    int i = 0;
    for (i = 0; environ[i] != NULL; ++i) {
        if (strncmp(string, environ[i], keylen) == 0) {
            environ[i] = string;
            pthread_mutex_unlock(&env_mutex);
            pthread_sigmask(SIG_SETMASK, &old, NULL);
            return 0;
        }
    }
    printf("env length: %d\n", i);
    if (!is_first_put) {
        is_first_put = 1;
        char** new_environ = malloc(sizeof(char*) * (i + 1));
        if (new_environ == 0) {
            fprintf(stderr, "fail to realloc environ\n");
            abort();
        }
        memcpy(new_environ, environ, sizeof(char*) * i);
        environ = new_environ;
    } else {
        environ = realloc(environ, sizeof(char*) * (i + 1));
    }
    if (environ == 0) {
        fprintf(stderr, "fail to realloc environ\n");
        abort();
    }
    environ[i] = string;
    environ[i + 1] = NULL;
    pthread_mutex_unlock(&env_mutex);
    pthread_sigmask(SIG_SETMASK, &old, NULL);
    return 0;
}
