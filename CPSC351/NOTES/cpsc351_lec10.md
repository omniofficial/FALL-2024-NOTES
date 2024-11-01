# LECTURE #10: Process Synchronization 3, 9/26/24

## Classical Problems of Synchronization

-   Illustrate challenges and caveats of process Synchronization

-   Used to test newly proposed Synchronization schemes
-   **Classical problems:**
    -   The bounded buffer problem
    -   The reader-writers problems
    -   The dining philosophers problem

## Classical Problems of Synchronization: The Bounded Buffer Problem

-   A pool of n buffers.
-   Two processes:

    -   A producer process adds buffers to the pool.
    -   A consumer process removes buffers from the pool.

-   Semaphores:
    -   Mutex:
        -   Enforces mutual exclusion to the buffer pool (i.e. only one process at a time may access the pool).
        -   Initialized to 1.
    -   empty:
        -   Counts the number of available buffers;
        -   Initialized to n.
    -   full:
        -   Counts the number of full buffers;
        -   Initialized to 0.

## Classical Problems of Synchronization: The Readers Writers Problem

-   A shared database.

-   Two sets of processes:

    -   Readers: only want to read the database.
    -   Writers: may read or modify the database.

-   How do we synchronize accesses to the database?

