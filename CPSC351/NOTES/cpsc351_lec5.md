# LECTURE #5: Interprocess Communications: CONTINUED, 9/12/24

## PIPES

-   `pipe(fd)` system call (where int fd[2]) creates a pipe where:

    -   fd[0] is the read end
    -   fd[1] is the write end

-   A parent creates a pipe and forks a child
-   The child inherits the pipe because pipes are treated as files
-   In Unix, data can be be read / written from the pipe, using `read()` and `write()` system calls.

## NAMED PIPES

-   Named pipes can also be created programatically using `mkfifo()` system call.
-   **Example:** `mkfifo(“myfifo”, S_IWUSR | S_IRUSR)`
    -   Will create a FIFO called "myfifo".
    -   The FIFO will be readable and writable by the user (i.e. the second paramater).
    -   The FIFO can be read or written using `fread()`, `fgets()`, `fstream()`, etc.

## SOCKETS

-   **Socket**: An endpoint of communications.
-   Pair of processes can communicate over the network
    using a pair of sockets.
-   A socket is identified by concatenating an IP address of the system and a port number on the system.
