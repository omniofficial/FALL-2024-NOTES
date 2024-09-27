// -------------------------------
// Assignment: Number #3_1
// Due date: 9/25/24
// Purpose: Write a program to read one token at a time from the given text file and determine whether the token is a number, identifier or reserved word.
// -------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstring>
using namespace std;

const char *reservedWords[] =
    {
        "while", "for", "switch", "do", "return"};

// Check if token is a number
bool isNumber(const string &token)
{
  // For any character in a token, if not a digit return false. Else, return true.
  for (char c : token)
  {
    if (!isdigit(c))
    {
      return false;
    }
  }
  return true;
}

// Check if function is an identifier
bool isIdentifier(const string &token)
{
  // The first character in a token must be a letter or an underscore
  if (!(isalpha(token[0]) || token[0] == '_'))
  {
    return false;
  }

  // Check if other letters are digits, underscores, or letters
  for (size_t i = 1; i < token.size(); ++i)
  {
    if (!(isalnum(token[i]) || token[i] == '_'))
    {
      return false;
    }
  }

  // If both conditions are satisfied, then return true.
  return true;
}

// Function to check if a token is a reserved word
bool isReserved(const string &token)
{
  for (const char *reservedWord : reservedWords)
  {
    // Compare two string character to character. If strcmp evaluates to 0 (meaning it is true) then return true.
    if (strcmp(token.c_str(), reservedWord) == 0)
    {
      return true;
    }
  }
  // If strings do not match between the token and the reservedWord array, then return false.
  return false;
}

int main()
{
  ifstream file("input.txt");
  string token;

  // While there is still input from the file
  while (file >> token)
  {
    if (isNumber(token))
    {
      cout << token << " is a number." << "\n";
    }
    else if (isIdentifier(token))
    {
      cout << token << " is an identifier." << "\n";
    }
    else if (isReserved(token))
    {
      cout << token << " is a reserved word." << "\n";
    }
    else
    {
      cout << token << " is neither a number, reserved word, nor an identifier." << "\n";
    }
  }

  file.close();
  return 0;
}