# LECTURE #6: Threads, 9/17/24

## What is a Thread?

-   **Thread:** A basic unit of CPU utilization.
-   A thread consists of:

    -   A program var: keeps track of which instruction to execute next.
    -   Register values: store the current working variables.
    -   Stack: keeps track of the program execution history.

-   Thread vs Process:

    -   **Process:** Used for grouping resources together.
    -   **Thread:** An entity scheduled for the execution on the CPU.

-   A classical process has a dedicated set of resources and a single thread of control.

-   Multithreading: Allows a process to have mutiple paralles threads of execution.

## Multithreading

-   **All threads share:** data section, code section, and opened files.

-   Each thread has its own program counter, registers, and stack.

-   **Key idea:** If a process has multiple threads, it can perform multiple tasks at a time.
-   **Example:** A web server is accessed by thousands of clients simultaneously. How can we service the clients?
    -   Single process: Services clients one at a time.
    -   Multiple processes: For each client, fork a copy of the server.
        -   Faster than a single process: multuple processes can services clients in parallel.
        -   Wasteful: If each process will perform identical tasks, then why duplicate ALL process resources?
    -   Multithreading: within the same server process, create a separeate thread for each client.

## Benefits of Multithreading

-   Resposiveness: Multithreaded application may continue running even if a part of the program is busy or blocked.

-   Resource sharing: All threads of a process share memory and resources.

-   Economy: Creating and managing a thread is faster than creating and managing a process:

    -   Most resources need not be cloned
    -   Thread context switch is faster than a process context switch.
    -   **Example:** Solaris
        -   Process creation is 30x slower than thread creation.
        -   Process context switch is 5x slower than thread context switch.

-   Stability: Multiple threads can execute in parallel on multiple processors.

## Muticore Programming

-   Multicore systems are persuasive:
    -   OS should support concurrent execution on multiple cores.
    -   Application developers: Should design multithreaded programs - a challenging task!

### Multithreading Models

-   Support for multiple threads may be provided at either the user level or by the kernel.
-   Two types of threads:

    -   User threads: Supported and managed without intervention from the OS:
        -   POSIX Threads
        -   Win32 Threads
        -   Java Threads
    -   Kernel threads: Supported and managed directly by the OS:
        -   Windows XP/2000
        -   Solaris
        -   Linux
        -   Tru64 Unix
        -   Mac OS X

-   Some relationship must exist between the user threads and the kernel threads.

## Thread Libriaries

### Overview

-   Thread library: Provides programmer with API for creating and managing threads.
-   Two primary ways of implementing a thread library:
    -   In user space; invoking an API function does not result in a system call.
    -   In kernel space: invoking an API function call results in a system call.
-   Three dormant libriaries:
    -   POSIX threads (pthreads)
    -   Win32
    -   Java

### Pthreads

-   `Pthreads`: POSIX specification for thread behavior

-   `pthread_join()`: Used by a parent thread to wait for a child thread to complete.
-   `pthread_exit():` Terminates the calling thread.
