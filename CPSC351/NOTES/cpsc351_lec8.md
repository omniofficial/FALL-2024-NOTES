# LECTURE #7: Process Synchronization 1, 9/24/24

## What is Process Synchronization?

-   Process Synchronization ensuring on orderly execution of cooperating processes that share data, in ordet to maintain data consistency.

    -   Necessary to prevent **race conditions**.

-   **Race conditions:** When multiple processes (or threads) access and manipulate the same data concurrently and the outcome of the execution depends on the particular order in which the access takes place.

## Race Conditions: Producer Consumer Problem

-   Bounded buffer implementation (a wrap-around buffer)
    -   Store the following variables in shared memory:

```cpp
#define BUFFER_SIZE 10
typedef struct {
. . .
} item;
item buffer[BUFFER_SIZE];
int counter = 0; //Keeps track of the # of full slots.
int in = 0; //First empty position in “buffer”
int out = 0; //First full position in “buffer”
//The buffer is empty when in == out
//The buffer is full when ((in+1) % BUFFER_SIZE) == out.
```

### Machine code for updating the counter:

```cpp
//Producer code:
PI1. register1 = counter
PI2. register1 = register1 + 1
PI3. counter = register1

//Consumer code:
CI1. register2 = counter
CI2. register2 = register2 - 1
CI3. counter = register2
```

-   PI = Producer instruction
-   CI = Consumer instruction
-   The concurrent execution of the above codes, may correspond to many
    different sequential executions.
-   The final value of the counter depends on the order of execution

## The Critical Section Problem

### Overview

-   **Critical Section:** A segment of process code, in which the process modifies shared resources e.g. updating a table or writing to a file.
-   No two processes may execute in the critical section at the same time e.g. no two processes may update the same variable at the same time.
-   **The critical section problem:** Ensuring that only one process is executing in its critical section.

### Solution Requirements

-   Requirements for solving the critical section problem:
    -   Mutual exclusion: only one process may enter a critical section at a time
    -   Progress: no process executing outside of its critical section, may block other
        processes from entering theirs
    -   Bounded waiting: process cannot be perpetually barred by other processes, from
        entering its critical section
-   **Existing solutions:**
    -   Peterson's solution: software-based solution.
    -   Synchronization hardware: hardware-based solution.
    -   Semaphores: specialized integer variables.

## Synchronization Hardware

-   Solution for uniprocess systems: disable interrupts while modifying a shared variable - if no other instructions are being executed, then nothing can interfere with the variable modification operation.

    -   Approach taken by nonpreemptive kernels.
    -   Difficult on multiprocessor systems.

-   Special atomic hardware instructions:
    -   `TestandSet()`: Can atomically test and then set the value of a variable.
    -   `Swap()`: Can atomically swap the contents of two variables.

## Semaphores

### Different Types

-   Counting Semaphores:

    -   The value is unrestricted
    -   Useful for coordinating access to a resource with finite number of instances
    -   The semaphore is initialized to the maximum # of instances
    -   When the process cals `wait()` it decrements the value of S:

        -   If 5 remains positive, then the process may continue executing.
        -   Otherwise, the process waits in a loop until 5 becomes positive.

    -   When the process calls `signal()`, it increments the value of 5.

## Implementation

-   The following implementation of mutex requires busy waiting i.e. constantly polling S in a loop:

```cpp
wait(S)
{
//Do nothing
while( S <= 0);
S--;
}
```

-   Works fine if the critical section is short; otherwise it is inefficient.
-   There are alternatives to busy waiting...

### Continued

-   With each semaphore associate a wait queue of processes (represented as a linked list)
-   Each entry in a queue compromises:
    -   Value (of type integer)
    -   Painter to next record in the list
-   Redefine `wait()` and `signal()` functions as follows:

```c++
// WAIT FUNCTION
wait(semaphore *S)
{ S->value--;
if (S->value < 0)
{ add this process to S->list;
block();
  }
}


// SIGNAL FUNCTION
signal(semaphore *S)
{ S->value++;
if (S->value <= 0)
{ remove a proc. P from S->list;
wakeup(P);
  }
}
```

-   `wait()`: if S->value is non-positive: the calling process is added to the list and is blocked (switched to waiting state).
-   `wakeup()`: if S->value <= 0, then a process is removed from the list and is woken up i.i. allowed to execute.
