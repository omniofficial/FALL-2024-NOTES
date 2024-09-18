// -------------------------------
// WORK IN PROGRESS... EVALUATES INCORRECTLY CURRENTLY
// Assignment: Number #2
// Due date: 9/17/24
// Purpose: Write a program to find the value of a postfix expression. Variables are one or more characters. Note: This is an updated program of the previous program.
// -------------------------------

#include <iostream>
#include <unordered_map>
#include <stack>
#include <stdexcept>
#include <sstream>
using namespace std;

// Algorithm to replace variables in the expression with their values
string varValues(string &expression, unordered_map<string, double> &values)
{
std:
  ostringstream numeric_expression;

  for (size_t i = 0; i < expression.length(); ++i)
  {
    char ch = expression[i];
    // If character pertains to a variable, look up the character in map. If it does not pertain to variable, directly move character operator to the end result.
    if (isalpha(ch))
    {
      string var(1, ch);
      auto it = values.find(var);
      if (it != values.end()) // Evaluate only if there are still values within the map
      {
        numeric_expression << it->second << " "; // assign double value to second string value (num1 = '10')
      }
    }
    else if (isdigit(ch) || (ch = '-' && i + 1 < expression.length() && isdigit(expression[i + 1])))
    {
      string num;
      while (isdigit(ch) || ch == '-')
      {
        num += ch;
        ch = expression[++i];
      }
      numeric_expression << num << " ";
      --i;
    }
    else // If all else fails, directly move char contents to numeric_expression string
    {
      numeric_expression << ch << " ";
    }
  }
  return numeric_expression.str();
}

// Evaluate postfix expression
double postfixEval(string &expression, unordered_map<string, double> &values)
{
  stack<double> s; // Creates a stack
  // Scans stack
  for (size_t i = 0; i < expression.length(); ++i)
  {
    char ch = expression[i];

    // CASE: If character is a digit:
    if (isdigit(ch))
    {
      string num;
      while (isdigit(ch))
      {
        num += ch;
        ch = expression[++i];
      }
      s.push(std::stod(num));
      --i;
    }

    // CASE: If character is a variable
    else if (isalpha(ch))
    {
      string var(1, ch);
      if (values.find(var) != values.end())
      {
        s.push(values.at(var));
      }
    }

    // CASE: If character is an operand, make sure to use the operand on the first two topmost characters of stack
    else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
    {
      // If operator = true, pop first two char out of stack
      double tempval;
      double char1 = s.top();
      s.pop();
      double char2 = s.top();
      s.pop();

      switch (ch)
      {
      case '+':
        s.push(char2 + char1);
        break;

      case '-':
        s.push(char2 - char1);
        break;

      case '*':
        s.push(char2 * char1);
        break;

      case '/':
        s.push(char2 / char1);
        break;
      }
    }
    else if (isspace(ch))
    {
      continue;
    }
  }
  return s.top();
}

int main()
{
  char choice;

  do
  {
    unordered_map<string, double> values;

    // Variable Values
    string expression;
    string variable;
    double varvalues;

    // Starting prompt
    cout << "Enter a postfix expression with $ at the end: \n";
    cin >> expression;
    cout << "\n";

    for (int i = 0; i < 2; ++i)
    {
      cout << "Enter variable name: ";
      cin >> variable;
      cout << "\n";
      cout << "Enter variable value: ";
      cin >> varvalues;
      cout << "\n";
      values[variable] = varvalues;
    }

    // Remove $ from the expression
    expression.pop_back();

    // Call varValues to convert string to numeric expression
    string numeric_expression = varValues(expression, values);

    // Evaluate and display the expression
    cout << "Value: " << postfixEval(numeric_expression, values);
    cout << "\nCONTINUE? (Y/N) ";
    cin >> choice;

  } while (choice != 'N' && choice != 'n');

  cout << "You have terminated the program.";
  return 0;
}