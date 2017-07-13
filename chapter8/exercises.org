* Process control
1. The *printf* does not return -1. This is because it is not closed on exit. We should use *fclose* to close stdout manually to get similar results.
2. The stack is broken by the child process. Thus, the father process exit with error.
3. See the program.
4. This is because after the parent write the results, the child is not waited. If we let child run first, there will be no such problem.
5. On my computer (Ubuntu 17.04), there is no difference. Since only *execvpe* is the syscall, it depends on *glibc*.
6. See the program.
7. *opendir* will set the fd to be closed on *exec*, but *open* does not.
