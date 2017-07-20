# Process Environment
1. I cannot get the exit code of 13. I guess that the compiler will add a *return 0* for me. I compare the executable file with or without *return 0*. They have no difference.
2. After *main* return to the *_start* procedure (gcc, Linux).
3. On Linux, the arguments can be read through */proc/self/cmdline*. Moreover, assembly language can be used to trace the stack manually.
4. It helps to find errors faster.
5. We need a array to store all the callbacks.
6. Yes.
7. Because they will change at runtime.
8. The symbol tables, debugging informations are not presented by *size*.
9. Even a simple program will use multiple libraries, such as stdio, stdlib.
10. If *val == 0*, the result is undefined.
