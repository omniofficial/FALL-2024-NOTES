# LECTURE #3: Processes 2, 9/5/24

## Operations on Processes: Process Creation in Linux: `fork()`

-   `fork()` system call is issued by a parent process to create a child process.
-   Child process is a clone of a parent process.
-   Both parent and child continue execution at the instruction immediatly after `fork()`:

    -   In the child `fork()` returns 0
    -   In the parent form returhsn process id
    -   `fork()` returns 0 upon failure.

-   The child process inherits:

    -   The set of files opened by the parent process
    -   All other resources..

-   `exec()`: replaced the program of the caller process with a new program.
-   `wait()`: waits until the child terminates.
-   `exit(int exitcode)`: terminates the caller process with the specific exit code.

## Operations on Processes: Process Creation in Linux: `exec()` variants

-   `pid_t wait (int *status);`
-   `pid_t waitpid(pid_t pid, int *status, int options);`
-   `int waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options);`
-   `wait()` and `waitpid()` return the process id of the child.
-   `waitid()` return 0 on success and -1 on failure.

## Interprocess Communications

### Types of Processes:

-   A process can either be:
    -   **Independent:** Cannot affect or be affected by other processes.
    -   **Cooperating:** Process that can affect or be affected by other processes:
        -   Example: If the process shares memory with other processes.
-   Cooperating processes need a mechanism to exchange information i.e. interprocess communications (IPC).

### Fundamental IPC models:

-   **Shared memory:** Cooperating processes exchange information by reading/writing data from/to a region of shared memory.
-   **Message passing:** Cooperating processes exchanege messages.

## Interprocess Communications: Shared Memory vs Message passing

### Shared Memory:

-   Faster than message passing: Only requires intervention from the OS to establish a shared memory region.
-   Good for large transfers of information.
-   **Disadvantage:** Requires process synchronization to ensure that no two processes write the same memory locatoin at the same time.

### Message Passing:

-   No need for synchronization
-   Good for small information transfers
-   Easier to implement than shared memory.
-   **Disadvantage:** Usually required OS intervention on every message transfer.

