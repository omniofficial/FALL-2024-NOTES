// -------------------------------
// Assignment: Number #1
// Due date: 9/10/24
// Purpose: This program reads an expression in postfix form, evaluates the expression and displays its value.
// -------------------------------

#include <iostream>
#include <unordered_map>
#include <stack>
using namespace std;

// Algorithm to replace variables in the expression with their values
string varValues(string &expression, unordered_map<char, int> &values)
{
  string numeric_expression;

  for (char ch : expression)
  {
    // If character pertains to the alphabet, look up character in map. If it does not pertain to alphabet, directly move character operator to the end result.
    if (isalpha(ch))
    {
      auto it = values.find(ch);
      if (it != values.end())
      {
        numeric_expression += to_string(it->second);
      }
      else
      {
        numeric_expression += ch;
      }
    }
    else
    {
      numeric_expression += ch;
    }
  }
  return numeric_expression;
}

// Evaluate postfix expression
int postfixEval(string numeric_expression)
{
  stack<int> s; // Creates a stack

  // Scans stack
  for (int i = 0; i < numeric_expression.length(); ++i)
  {

    // CASE: If character is a digit:
    if (isdigit(numeric_expression[i]))
    {
      s.push(numeric_expression[i] - '0');
    }

    // CASE: If character is an operand, make sure to use the operand on the first two topmost characters of stack
    else
    {
      int tempval;
      int char1 = s.top();
      s.pop();
      int char2 = s.top();
      s.pop();

      switch (numeric_expression[i])
      {
      case '+':
        tempval = char2 + char1;
        break;
      case '-':
        tempval = char2 - char1;
        break;
      case '*':
        tempval = char2 * char1;
        break;
      case '/':
        tempval = char2 / char1;
        break;
      }
      s.push(tempval);
    }
  }
  return s.top();
}

int main()
{
  char choice;

  do
  {
    // Variable Values
    int a = 5;
    int b = 7;
    int c = 2;
    int d = 4;
    string expression;

    // Initialize variables
    unordered_map<char, int> values = {
        {'a', a},
        {'b', b},
        {'c', c},
        {'d', d}};

    // Starting prompt
    cout << "Enter a postfix expression with $ at the end: \n";
    cin >> expression;
    cout << "\n";

    // Remove $ from the expression
    expression.pop_back();

    // Call varValues to convert string to number
    string numeric_expression = varValues(expression, values);

    // Evaluate and display the expression
    cout << "Value: " << postfixEval(numeric_expression);
    cout << "\nCONTINUE? (Y/N) ";
    cin >> choice;

  } while (choice != 'N' && choice != 'n');

  cout << "You have terminated the program.";
  return 0;
}
