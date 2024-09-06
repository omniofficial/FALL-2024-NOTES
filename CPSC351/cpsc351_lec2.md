# LECTURE #2: Processes 1, 9/3/24

## Processes

-   Process: a unit of work on the system
-   Recall: Program vs Processes:
    -   Program: is a set of instructions
    -   Process: a program in execution
-   Processes need resources: CPU, memory, files, and I/O devices.
-   Applications vs Process: an application may consist of multiple processes.

## Process Memory

-   Stack: stores function parameters, local variables, and return address.
-   Heap: contains dynamic memory allocated during process runtime.
-   Data: contains global variables
-   Text: stores the program instructions (the executable).

## Process States

-   The states of a process:
    -   New: Process being created.
    -   Running: Intructions are being executed.
    -   Waiting: Process is waiting for some event (I/O completion).
    -   Ready: Process waiting to be assigned to processor.
    -   Terminated: The process has finished execution.

## Process States in Linux

-   Can learn process state using the **ps utility**:
    -   Example: `ps-aux`
-   Interpreting the output of ps:
    -   **R** the process is running or runnable (on run queue)
    -   **D** uninterruptible sleep (usually I/O)
    -   **S** interruptible sleep (waiting for an event to complete)
    -   **Z** defunct/zombie, terminated but not reaped by its parent
    -   **T** stopped, either by a job control signal or because it is being traced.

## Process Control Block

-   To represent each process, the OS uses **Process Control Block (PCB)**
-   PCB Components:

    -   **Process State:** the state of the process e.g. Running.
    -   **Process ID:** a unique ID associated with the process e.g. 123
    -   \*Program Counter:\*\* the address of the next instruction to be executed
    -   **CPU Registers:** the current values of the accumulators, stack pointers, etc.
    -   **CPU- Scheduling Information:** e.g. priority...
    -   **Memory Management Information**
    -   **Accounting Information**
    -   **I/O Status Information**

-   **Example:** in Linux OS, PCB is represented using `struct task_struct` which contain:
    -   `struct mm_struct mm`

## Process Scheduling: Schedulers

### Short term:

-   Invoked frequently
-   Has to be efficient

### Long term:

-   **Question:** What if we have more processes that can fit into memory?
-   **Answer:** No problem! Spool (temporarily store) some processes on a **mass storage** device (hard drive)
-   **Long term scheduler:** Selects spooled processes to load from the mass storage device into main memory.
-   Executes **less frequently** than a short term scheduler.

**Key Idea:** Maximize resource utilization by selecting a mix of CPU bound and I/O bound processes:

-   **I/O bounds processes**: Processes that spend more time doing I/O operations than CPU compuations.
-   **CPU bound processes:** Processes that spend more time doing CPU computations than I/O operations.

### Medium Term:

-   Removes some processes from memory in order to improve the process mix.
-   Later, the removed processes can be brought into memory.
-   This is known as **swapping**.

## Process Scheduling: Context Switching

-   Context Switch: Switching CPU between processes:
    1. Save **CPU state** of the currently executing process into a PCB.
    2. Select another process.
    3. Use the **saved PCB** of the selected process to initialize the CPU.
    4. Let the selected process **resume** execution.
-   Context switch time is **pure overhead!**

## Operations on Processes

-   A process may create new processes by issuing a process creating system.

    -   Parent process: The creator process.
    -   Child process: The process created by the parent.
    -   **Linux:** Display processes using the command `htop`.

-   After creating a child process a parent process may:
    -   Continue executing.
    -   OR wait for the child process to terminate.
-   The child process can either:
    -   Be a duplicate of the parent process (same data, etc).
    -   May be running a new program.
  - 
  - 
