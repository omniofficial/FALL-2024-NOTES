// CLASSROOM ACTIVITY - 9/10/24
// ------------------------------------
// Task: Write a program using fork(), execlp(), and wait(). Create a parent process that forks a child to execute below listed command. Ensure the parent waits for the child to terminate before exiting.(ps, date, top). 

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    printf("Program starts: I am the parent process, and my job is to create a child process.\n");

    // This command creates a child process:
    pid_t pid = fork();

    // Check if the fork failed:
    if(pid < 0)
    {
        // If fork fails, print an error message
        perror("Fork failed: Couldn't create a child process.");
        exit(-1);
    }

    // If pid is 0, we are inside the child process
    else if(pid == 0)
    {
        printf("Hello! I am the child process. My pid is: %d\n", getpid());
        printf("I am going to replace myself with another program using execlp.\n");

        // Replace the child process with the 'g++' command to compile 'a.cpp'
       //if(execlp("usr/bin/ls", "ls") < 0)
        if(execlp("/usr/bin/g++", "g++", "a.cpp", "-o", "a", NULL) < 0)
        {
            perror("execlp failed: Couldn't execute the g++ command.");
            exit(-1);
        }

        // If the execlp is successful, this line will never be printed
        printf("This line will not be printed if execlp works as expected.\n");
    }

    // Else, we are inside the parent process
    else
    {
        printf("I am the parent process. I have successfully created a child with pid: %d\n", pid);

        // Let the parent print that it is waiting for the child
        printf("The parent is now waiting for the child to complete its task...\n");

        // Wait for the child process to terminate and get its exit status
        int status;
        int retProcessPid = wait(&status);

        printf("My child with pid=%d has finished execution.\n", retProcessPid);

        // Check if the child terminated normally
        if(WIFEXITED(status))
        {
            printf("My child exited normally with exit code: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("My child did not exit normally.\n");
        }

        printf("Now, I (the parent process) will continue and end the program.\n");
    }

    return 0;
}