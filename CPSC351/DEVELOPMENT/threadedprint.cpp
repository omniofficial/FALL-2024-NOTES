#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
// Function for the first thread
void *threadFunc1(void *arg)
{
  for (int i = 0; i < 5; i++)
  {
    printf("Thread 1 is running...\n");
    sleep(1); // Pause for 1 second
  }
  return NULL;
}
// Function for the second thread
void *threadFunc2(void *arg)
{
  for (int i = 0; i < 5; i++)
  {
    printf("Thread 2 is running...\n");
    sleep(1); // Pause for 1 second
  }
  return NULL;
}
int main()
{
  // Declare two thread variables
  pthread_t thread1, thread2;
  // Create the first thread
  if (pthread_create(&thread1, NULL, threadFunc1, NULL) != 0)
  {
    perror("Failed to create thread 1");
    return 1;
  }
  // Create the second thread
  if (pthread_create(&thread2, NULL, threadFunc2, NULL) != 0)
  {
    perror("Failed to create thread 2");
    return 1;
  }
  // Wait for both threads to finish
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  printf("Both threads have finished execution.\n");
  return 0;
}
