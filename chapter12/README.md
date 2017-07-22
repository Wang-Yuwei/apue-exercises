# Thread Control
1. The stdout would be full buffered. "parent about to fork..." would be printed twice as it is not flushed to the stdout.
2. See the program.
3. No, some functions in **getenv** might unblock the signals.
4. Skipped. (I have no BSD)
5. Sometimes, we want to run another program. Sometimes, we do not want to kill the whole process on errors.
6. We can use conditional variable with timeout. Signals do not play well in a multi-threaded program.
7. It depends on the implementation of conditional variables.
8. We can use absolute time in clock\_nanosleep.
