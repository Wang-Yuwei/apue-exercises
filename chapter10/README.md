# Signals
1. It can only receive one signal.
2. See the program.
3. main -> sleep -> sig\_int -> sig\_alrm
4. If the signal is fired before **setjmp** (on a heavy system), the **longjmp** will goes error.
5. This problem is much more difficult than it seems. We need a priority queue for different to arrange the timers, but it is quite difficult to implement it with only reentryable functions.
6. See the program.
7. **_exit** means normally termination, but POSIX **abort** requires an abnormal termination.
8. The effective user ID might be the same with the receiver or the root. Real user ID contains more information.
9. See the program.
10. Time error accumulates with **sleep** calls. **cron** can check the wall time after waking up and then calculate the time to sleep for next 60 seconds.
11. See the program.
12. See the program. **write** can be completed.
