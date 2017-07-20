# Exercises for chapter 4
1. See the program.
2. The access mode of every file created by the process would be set to 0000. It can not be accessed by any one until its access mode is changed.
3. We can use *chmod* to verify it.
4. The files can not be created again.
5. No, the size of an empty directory is one block (4096 bytes on my computer), and a symbolic link should save the path it points to.
6. See the program. I use non POSIX extension *SEEK_DATA* and *SEEK_HOLE* to do the exercise.
7. Shell set the access model for file.hole.
8. This is because the file is unlinked, we cannot visit it with *du*.
9. This is because *unlink* changes the reference count in inode.
10. It limits the max number of open directories.
11. According to my experiments, using *chdir* is about 9% faster.
12. It can be used to forbid a process visiting the files out of a directory. It is useful when we want to run a untrustable process.
13. Use *stat* to get the current value first.
14. New mail received is the last modified time. Unread since is the last access time.
15. They save the last modified time. When the files are unarchived, the access time is the time unarchving the files.
16. On my computer, the *ext4* filesystem has unlimited full path length.
17. I cannot unlink /dev/fd/1, but I can still create /dev/fd/1.
