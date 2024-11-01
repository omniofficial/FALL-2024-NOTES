// -------------------------------
// Assignment: Number #7_2
// Due date: 10/30/24
// Purpose: A modification of the previous program to include the new CFG and Parsing Table.
// -------------------------------

#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int NON_TERMINALS = 7;
const int TERMINALS = 10;

// Indexes of Non-Terminals
const int S = 0;
const int W = 1;
const int E = 2;
const int Q = 3;
const int T = 4;
const int R = 5;
const int F = 6;

// Indexes of Terminals
const int T_A = 0;     // 'a'
const int T_B = 1;     // 'b'
const int T_PLUS = 2;  // '+'
const int T_MINUS = 3; // '-'
const int T_STAR = 4;  // '*'
const int T_SLASH = 5; // '/'
const int T_OPEN = 6;  // '('
const int T_CLOSE = 7; // ')'
const int T_EQUAL = 8; // '='
const int T_X = 9;     // 'x'

// Array to map characters to terminal indices
const char terminals[TERMINALS] = {'a', 'b', '+', '-', '*', '/', '(', ')', '=', 'x'};

// Define an array to map non-terminal characters to their indices
const char nonTerminals[NON_TERMINALS] = {'S', 'W', 'E', 'Q', 'T', 'R', 'F'};

// Initialize the Parsing Table
string table[NON_TERMINALS][TERMINALS] = {
    {"aW", "x", "x", "x", "x", "x", "x", "x", "x", "x"},    // Row S
    {"x", "x", "x", "x", "x", "x", "x", "x", "=E", "x"},    // Row W
    {"TQ", "TQ", "x", "x", "x", "x", "TQ", "x", "x", "x"},  // Row E
    {"x", "x", "+TQ", "-TQ", "x", "x", "x", "l", "x", "l"}, // Row Q
    {"FR", "FR", "x", "x", "x", "x", "FR", "x", "x", "x"},  // Row T
    {"x", "x", "l", "l", "*FR", "/FR", "x", "l", "x", "l"}, // Row R
    {"a", "b", "x", "x", "x", "x", "(E)", "x", "x", "x"},   // Row F
};

// Get Terminal Index function
int getTerminalIndex(char c)
{
  for (int i = 0; i < TERMINALS; i++)
  {
    if (terminals[i] == c)
    {
      return i;
    }
  }
  return -1; // Invalid terminal
}

// Function to parse user input
void parse(const string &input)
{
  // Initialize stack
  stack<char> parsingStack;
  // Push the starting symbol and trailing $
  parsingStack.push('$');
  parsingStack.push('S');

  string output;
  size_t index = 0;

  // Run whenever stack is not empty
  while (!parsingStack.empty())
  {
    char top = parsingStack.top();
    char currentInput = (index < input.length()) ? input[index] : '$';

    // Display stack
    output += "Stack: ";
    // Create a temp stack to keep track of stack contents
    stack<char> temp = parsingStack;

    while (!temp.empty())
    {
      output += temp.top();
      temp.pop();
    }
    output += "\n";

    if (top == currentInput)
    {
      parsingStack.pop();
      index++;
    }
    // Check if top symbol of parsing stack is uppercase. If it is true, then it is a non-terminal symbol
    else if (isupper(top))
    {
      parsingStack.pop(); // Remove the non-terminal from the stack

      // Find the index of the non-terminal
      int nonTerminalIndex = -1;
      for (int i = 0; i < NON_TERMINALS; i++)
      {
        if (nonTerminals[i] == top)
        {
          nonTerminalIndex = i;
          break;
        }
      }

      int terminalIndex = getTerminalIndex(currentInput);
      if (terminalIndex != -1 && nonTerminalIndex != -1)
      {
        string production = table[nonTerminalIndex][terminalIndex];

        // Look for blanks (represented as "x"), input will be rejected if production == "x"
        if (production == "x")
        {
          output += "Error: No production for " + string(1, top) + " with " + currentInput + "\n";
          break;
        }

        for (int i = production.length() - 1; i >= 0; i--)
        {
          if (production[i] != 'l') // Skip lambda productions
          {
            parsingStack.push(production[i]);
          }
        }
      }
      else
      {
        output += "Error: No production for " + string(1, top) + " with " + currentInput + "\n";
        break;
      }
    }
    else
    {
      // Error
      output += "Error: Unexpected symbol " + string(1, top) + "\n";
      break;
    }
  }

  // Empty stack conditions
  // Make sure all the stack is empty and the entire string has been processed
  if (parsingStack.empty() && index == input.length())
  {
    output += "Input string is accepted\n";
  }
  // Stack is empty and index is less than the length of the string
  else if (parsingStack.empty() && index < input.length())
  {
    output += "Input string has been rejected\n";
  }
  // Stack is empty, but all that is left at the top of the stack is $
  else if (!parsingStack.empty() && parsingStack.top() == '$' && index == input.length())
  {
    output += "Input string is accepted\n";
  }
  else
  {
    output += "Input string rejected.\n";
  }

  cout << output;
}

int main()
{
  string input; // Input string
  cout << "Enter the input string (put a $ at the end of the expression): ";
  getline(cin, input);

  parse(input);
  return 0;
}
