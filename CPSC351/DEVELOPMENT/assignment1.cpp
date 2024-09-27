// -------------------------------
// Assignment: Number #1 - Parallel Text Processing
// Due date: 9/24/24
// Purpose: Write a C/C++ program that uses multiple threads to count the number of vowels in separate strings.  //Each thread will process one string and compute the count of vowels in it.
// -------------------------------

#include <iostream>
#include <cstring>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const int NUM_THREADS = 3; // Three threads will be created
char strings[NUM_THREADS][100];
int vowelCounts[NUM_THREADS];

// Count Vowels function
int countVowels(const char str[])
{
  int count = 0;
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u' ||
        str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U')
    {
      count++;
    }
  }
  return count;
}

// Thread function to count vowels in a specific string
void *threadFunc(void *arg)
{
  // Retrieve the index of the string from pointing arg to (&threadIndex[i]), pass it into the countVowels function and store the index in the proper vowelCount array.
  int index = *(int *)arg;
  vowelCounts[index] = countVowels(strings[index]);
  pthread_exit(NULL);
}

int main()
{
  // Initialize strings
  char str1[] = "Hello World";
  char str2[] = "Example String";
  char str3[] = "Thread Example";

  // Copy strings into stringsarray
  strcpy(strings[0], str1);
  strcpy(strings[1], str2);
  strcpy(strings[2], str3);

  // Define threads and thread indexes
  pthread_t threads[NUM_THREADS];
  int threadIndex[NUM_THREADS];

  // Run a for loop to create a thread depending on the NUM_THREADS value
  for (int i = 0; i < NUM_THREADS; i++)
  {
    threadIndex[i] = i;
    // Pass argument (void *)&threadIndex[i])
    if (pthread_create(&threads[i], NULL, threadFunc, (void *)&threadIndex[i]) != 0)
    {
      perror("Failed to create thread");
      return 1;
    }
  }

  // Wait for all threads to finish
  for (int i = 0; i < NUM_THREADS; i++)
  {
    pthread_join(threads[i], NULL);
  }

  // Output the array elements and the vowel count
  for (int i = 0; i < NUM_THREADS; i++)
  {
    cout << "Thread processing string " << (i + 1) << ": " << "'" << strings[i] << "'" << " - Vowels: " << vowelCounts[i] << endl;
  }

  return 0;
}
