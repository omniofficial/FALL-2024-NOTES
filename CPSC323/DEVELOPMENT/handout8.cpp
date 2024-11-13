// -------------------------------
// Assignment: Number #8
// Due date: 11/13/24
// Purpose: Given the following CFG and the LR Parsing table. Write a program to trace the input strings: (i+i)*$ and (i*)$ to determine whether they satisfy the given CFG or not.
// -------------------------------

#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int STATES = 16;
const int TERMINALS = 8;
const int NON_TERMINALS = 3;

// Terminal Array
const char terminals[TERMINALS] = {'i', '+', '-', '*', '/', '(', ')', '$'};

// Non-Terminal Array
const char nonTerminals[NON_TERMINALS] = {'E', 'T', 'F'};

// Initialize the LR Parsing Table
string parsingTable[STATES][TERMINALS + NON_TERMINALS] = {
    //     i     +     -     *     /     (     )     $     E     T     F
    {"S5", "b", "b", "b", "b", "S4", "b", "b", "1", "2", "3"},     // State 0
    {"b", "S6", "S7", "b", "b", "TQ", "b", "ACC", "b", "b", "b"},  // State 1
    {"b", "R3", "R3", "S8", "S9", "b", "R3", "R3", "b", "b", "b"}, // State 2
    {"b", "R6", "R6", "R6", "R6", "b", "R6", "R6", "b", "b", "b"}, // State 3
    {"S5", "b", "b", "b", "b", "S4", "b", "b", "10", "2", "3"},    // State 4
    {"b", "S6", "S7", "b", "b", "b", "S15", "b", "b", "b", "b"},   // State 5
    {"S5", "b", "b", "b", "b", "S4", "b", "b", "11", "3", "b"},    // State 6
    {"S5", "b", "b", "b", "b", "S4", "b", "b", "12", "3", "b"},    // State 7
    {"S5", "b", "b", "b", "b", "S4", "b", "b", "b", "13", "b"},    // State 8
    {"S5", "b", "b", "b", "b", "S4", "b", "b", "b", "b", "14"},    // State 9
    {"b", "S6", "S7", "b", "b", "b", "S15", "b", "b", "b", "b"},   // State 10
    {"b", "R1", "R1", "S8", "S9", "b", "R1", "R1", "b", "b", "b"}, // State 11
    {"b", "R2", "R2", "S8", "S9", "b", "R2", "R2", "b", "b", "b"}, // State 12
    {"b", "R4", "R4", "R4", "R4", "b", "R4", "R4", "b", "b", "b"}, // State 13
    {"b", "R5", "R5", "R5", "R5", "b", "R5", "R5", "b", "b", "b"}, // State 14
    {"b", "R7", "R7", "R7", "R7", "b", "R7", "R7", "b", "b", "b"}, // State 15
};

// Stack initialization
stack<int> stateStack;
stack<char> symbolStack;

// printStacks function, prints both the stateStack and symbolStack
void printStacks()
{
  cout << "State Stack: ";
  stack<int> tempStateStack = stateStack;
  while (!tempStateStack.empty())
  {
    cout << tempStateStack.top() << " ";
    tempStateStack.pop();
  }
  cout << endl;

  cout << "Symbol Stack: ";
  stack<char> tempSymbolStack = symbolStack;
  while (!tempSymbolStack.empty())
  {
    cout << tempSymbolStack.top() << " ";
    tempSymbolStack.pop();
  }
  cout << endl;
}

// Shift function
void shift(int state, char terminal)
{
  stateStack.push(state);
  symbolStack.push(terminal);
  cout << "Shifted: " << terminal << " to state " << state << endl;
  printStacks(); // Display contents after undergoing a shift action
}

// Reduction function
void reduce(int ruleNumber)
{
  int rhsLength;
  char lhs;

  switch (ruleNumber)
  {
  case 0:
  case 1: // E -> E + T | E -> E - T
    rhsLength = 3;
    lhs = 'E';
    break;
  case 2: // E -> T
    rhsLength = 1;
    lhs = 'E';
    break;
  case 3:
  case 4: // T -> T * F | T -> T / F
    rhsLength = 3;
    lhs = 'T';
    break;
  case 5: // T -> F
    rhsLength = 1;
    lhs = 'T';
    break;
  case 6: // F -> ( E )
    rhsLength = 3;
    lhs = 'F';
    break;
  case 7: // F -> i
    rhsLength = 1;
    lhs = 'F';
    break;
  default:
    cout << "Invalid rule!" << endl;
    return;
  }

  // Rule #n A - B, pop right hand side
  for (int i = 0; i < rhsLength; ++i)
  {
    stateStack.pop();
    symbolStack.pop();
  }

  int nextState = stateStack.top();
  switch (lhs)
  {
  case 'E':
    nextState = 1;
    break;
  case 'T':
    nextState = 2;
    break;
  case 'F':
    nextState = 3;
    break;
  }

  stateStack.push(nextState);
  symbolStack.push(lhs);

  // Output both stack contents
  cout << "Reduced to: " << lhs << " in state " << nextState << endl;
  printStacks();
}

// Function to parse user input
void parse(const string &input)
{
  string inputStr = input + "$";

  // Initialize inputIndex
  int inputIndex = 0;

  // Initialize stateStack
  stateStack.push(0);

  while (true)
  {
    char currentInput = inputStr[inputIndex];

    // Find terminal index
    int terminalIndex = -1;
    for (int i = 0; i < TERMINALS; ++i)
    {
      if (currentInput == terminals[i])
      {
        terminalIndex = i;
        break;
      }
    }

    if (terminalIndex == -1)
    {
      cout << "Invalid input symbol!" << endl;
      break;
    }

    // Look into the parsing table to see if we should shift, reduce, or accept input.
    string action = parsingTable[stateStack.top()][terminalIndex];

    // Similar to previous program, blank states are represented by the letter b. If array content = b, then reject the input.
    if (action == "b")
    {
      cout << "Parsing error. Rejecting input." << endl;
      break;
    }
    // Display the contents of the current state, look ahead symbol, and desirde action
    cout << "State: " << stateStack.top() << ", Symbol: " << currentInput << ", Action: " << action << endl;

    if (action[0] == 'S')
    { // Apply the shift rule
      shift(stoi(action.substr(1)), currentInput);
      ++inputIndex;
    }
    // Apply the reduction rule
    else if (action[0] == 'R')
    {
      int ruleIndex = stoi(action.substr(1)) - 1;
      reduce(ruleIndex);
    }
    // If array = ACC, then the input string is accepted
    else if (action == "ACC")
    {
      cout << "Input accepted!" << endl;
      break;
    }
  }
}

// Main function
int main()
{
  string input;
  cout << "Enter the input string (make sure to end with $): ";
  cin >> input;

  parse(input);

  return 0;
}
