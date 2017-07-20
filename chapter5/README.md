* Chapter 5. Standard I/O library
1. I write the program according to the man page on Ubuntu 17.04.
2. The line will be printed to output through multiple function call, but the result is correct.
3. It means we are printing an empty string.
4. The return type of *getchar* is *int*. On some machines, *EOF* can be stored in *char*, but on other machines, it cannot.
5. Use *fflush* first, then use *fileno* to get the integer file descriptor.
6. The https://www.gnu.org/software/libc/manual/html_node/Flushing-Buffers.html mentioned that *glibc* will flush the buffer before doing input operations. However, it is not documented in *ISO C*. In addition, if I use *setbuf* to change the *stdout* to full buffer mode, the content will not show on the shell. 
7. I have no BSD system, so I have to skip the exercise. 
