// -------------------------------
// Assignment: Number #3_2
// Due date: 9/25/24
// Purpose: Write a program to determine whether an input string is accepted or rejected by the grammar in c++
// -------------------------------

#include <iostream>
#include <string>
#include <stddef.h>
std::string input;
size_t index = 0;

bool S();
bool B();
bool C();

// S -> aS | bB | cC
bool S()
{
  if (index < input.length())
  {
    if (input[index] == 'a')
    {
      index++;
      return S();
    }
    else if (input[index] == 'b')
    {
      index++;
      return B();
    }
    else if (input[index] == 'c')
    {
      index++;
      return C();
    }
  }
  return false;
}

// GRAMMAR: B -> bB | aC | λ
bool B()
{
  if (index < input.length())
  {
    if (input[index] == 'b')
    {
      index++;
      return B();
    }
    else if (input[index] == 'a')
    {
      index++;
      return C();
    }
  }
  return true;
}

// GRAMMAR: C -> aS | λ
bool C()
{
  if (index < input.length())
  {
    if (input[index] == 'a')
    {
      index++;
      return S();
    }
  }
  return true; // λ production (empty string)
}

int main()
{
  std::cout << "Enter a string: ";
  std::getline(std::cin, input);

  index = 0;

  // Check if string is accepted.
  if (S() && index == input.length())
  {
    std::cout << "The string is accepted." << std::endl;
  }
  else
  {
    std::cout << "The string is rejected." << std::endl;
  }

  return 0;
}
