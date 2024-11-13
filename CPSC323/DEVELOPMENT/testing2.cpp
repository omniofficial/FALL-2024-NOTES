#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Number of states and symbols
const int STATES = 16;       // 16 states
const int TERMINALS = 8;     // 8 terminal symbols (i, +, -, *, /, (, ), $)
const int NON_TERMINALS = 3; // 3 non-terminal symbols (E, T, F)

// Terminal Symbols: i, +, -, *, /, (, ), $
const char terminals[TERMINALS] = {'i', '+', '-', '*', '/', '(', ')', '$'};

// Non-terminal Symbols: E, T, F
const char nonTerminals[NON_TERMINALS] = {'E', 'T', 'F'};

// LR Parsing Table (States x (Terminals + Non-Terminals))
// Table: [State][Terminal/NonTerminal] = Action/Transition
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

// Stack for states and symbols
stack<int> stateStack;
stack<char> symbolStack;

// Function to perform a shift operation
void shift(int state, char terminal)
{
  stateStack.push(state);
  symbolStack.push(terminal);
  cout << "Shifted: " << terminal << " to state " << state << endl;
}

// Function to perform a reduction operation based on the rule number
void reduce(int ruleNumber)
{
  int rhsLength;
  char lhs;

  // Define the length of the right-hand side of each rule
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

  // Pop the stack for each symbol on the right-hand side of the rule
  for (int i = 0; i < rhsLength; ++i)
  {
    stateStack.pop();
    symbolStack.pop();
  }

  // Get the state for the non-terminal (lhs) from the parsing table
  int nextState = stateStack.top();
  switch (lhs)
  {
  case 'E':
    nextState = 1; // Example transition, could be modified
    break;
  case 'T':
    nextState = 2; // Example transition
    break;
  case 'F':
    nextState = 3; // Example transition
    break;
  }

  // Push the non-terminal and the new state
  stateStack.push(nextState);
  symbolStack.push(lhs);

  cout << "Reduced to: " << lhs << " in state " << nextState << endl;
}

// Function to parse the input string
void parse(const string &input)
{
  string inputStr = input + "$"; // Append '$' to signal end
  int inputIndex = 0;

  // Initialize stack with state 0
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

    // Invalid input symbol
    if (terminalIndex == -1)
    {
      cout << "Invalid input symbol!" << endl;
      break;
    }

    // Fetch the action from parsing table
    string action = parsingTable[stateStack.top()][terminalIndex];

    if (action == "b")
    {
      cout << "Parsing error. Rejecting input." << endl;
      break;
    }

    cout << "State: " << stateStack.top() << ", Symbol: " << currentInput << ", Action: " << action << endl;

    if (action[0] == 'S')
    { // Shift
      shift(stoi(action.substr(1)), currentInput);
      ++inputIndex;
    }
    else if (action[0] == 'R')
    { // Reduce
      int ruleIndex = stoi(action.substr(1)) - 1;
      reduce(ruleIndex);
    }
    else if (action == "ACC")
    { // Accept
      cout << "Input accepted!" << endl;
      break;
    }
  }
}

int main()
{
  string input;
  cout << "Enter input string (end with '$'): ";
  cin >> input;

  parse(input);

  return 0;
}
