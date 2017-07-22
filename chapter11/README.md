# Threads
1. See the program. We should allocate the struct on the heap.
2. We should acquire a write lock while changing the ID. However, there might be a time gap between **job_find** and **job_remove**. Hence, the ID might be changed between the two function calls. We should handle the problem.
3. Skipped. (I have done it before)
4. The first is better as it can support muliple waiters, while the second can support only one waiter.
5. Skipped. (I have done it before)
