# Daemon Process
1. It cannot open /dev/log any more.
2. This is because it has to print some messages to the terminal. However, on my computer, **rsyslogd** is a session leader.
3. Skipped (too much).
4. I get error "Inappropriate ioctl for device".
