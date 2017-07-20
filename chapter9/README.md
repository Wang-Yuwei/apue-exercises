# Process Relationships
1. Because the login process changes the user id for itself and run shell by *exec*, it can not modify utmp and wtmp any more. Thus, init process will take charge of it. For internet login, the inetd process will modify the two files.
2. See the program.
