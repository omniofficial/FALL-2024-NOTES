#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int NON_TERMINALS = 5;
const int TERMINALS = 8;

// Indexes of Non-Terminals
const int E = 0;
const int Q = 1;
const int T = 2;
const int R = 3;
const int F = 4;

// Indexes of Terminals
const int T_I = 0;      // 'i'
const int T_PLUS = 1;   // '+'
const int T_MINUS = 2;  // '-'
const int T_STAR = 3;   // '*'
const int T_SLASH = 4;  // '/'
const int T_OPEN = 5;   // '('
const int T_CLOSE = 6;  // ')'
const int T_DOLLAR = 7; // '$'

// Array to map characters to terminal indices
const char terminals[TERMINALS] = {'i', '+', '-', '*', '/', '(', ')', '$'};

// Define an array to map non-terminal characters to their indices
const char nonTerminals[NON_TERMINALS] = {'E', 'Q', 'T', 'R', 'F'};

// Initialize the Parsing Table
string table[NON_TERMINALS][TERMINALS] = {
    {"TQ", "b", "b", "b", "b", "TQ", "b", "b"},   // Row E
    {"b", "+TQ", "-TQ", "b", "b", "b", "l", "l"}, // Row Q
    {"FR", "b", "b", "b", "b", "FR", "b", "b"},   // Row T
    {"b", "l", "l", "*FR", "/FR", "b", "l", "l"}, // Row R
    {"i", "b", "b", "b", "b", "(E)", "b", "b"}    // Row F
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
  parsingStack.push('E');

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

        // Look for blanks, input will be rejected if production == b
        if (production == "b")
        {
          output += "Error: Blank production for " + string(1, top) + " with " + currentInput + "\n";
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
  // Make sure all the stack is emtpy and the entire string has been processed
  if (parsingStack.empty() && index == input.length())
  {
    output += "Input string is accepted\n";
  }
  // Stack is empty and index is less that the length of the string
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
