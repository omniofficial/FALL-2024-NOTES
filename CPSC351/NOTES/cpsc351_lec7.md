# LECTURE #7: Threads CONTINUED, 9/17/24

## Semnatics of `fork()` and `exec()`

### Overview
-   **Recall:** `fork()` system call duplicates the entire process.

-   If one thread calls `fork()`, do we duplicate all threads in a process? Is the forked process single threaded?

-   Does `fork()` duplicate only the calling thread or all threads?

### Threading Issues: Cancellation

-   Thread cacnellation: Terminating a thread before it has completed its task.

    -   **Asynchronous cancellation:** a thread is terminated immediatly upon request.
        -   Problem: terminated thread may not get a chance to release allocated resources.
    -   **Deffered cancellation:** a thread periodocally checks whether it should exit:
        -   Allows a thread to release its resource prior to exiting.

### Threading Issues: Signal Handling

-   **Signal:** Used in UNIX to notify a process that a particular event has occurred.

-   A signal can be either **synchronous** or **asynchronous**.
    -   **Synchronous:** Signal resulting form the process operaitons
    -   **Asynchronous:** Signal generated outside...



