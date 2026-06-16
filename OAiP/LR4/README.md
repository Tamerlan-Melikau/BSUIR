# Reverse Polish Notation Calculator in C++

A C++ console application that converts an infix mathematical expression into Reverse Polish Notation (RPN) and evaluates the result using stack-based algorithms.

## Features

* Converts infix expressions to Reverse Polish Notation (RPN)
* Supports arithmetic operators:

  * Addition (`+`)
  * Subtraction (`-`)
  * Multiplication (`*`)
  * Division (`/`)
* Supports parentheses for operation precedence
* Uses stacks for expression conversion and evaluation
* Allows variables (`a-z`) in expressions
* Requests variable values from the user during evaluation
* Detects division by zero
* Evaluates the final expression and displays the result

## Algorithms

### Infix to RPN Conversion

The program uses a stack-based algorithm to transform a standard mathematical expression into postfix notation according to operator precedence and parentheses.

### RPN Evaluation

The generated postfix expression is evaluated using a numeric stack. Operands are pushed onto the stack, and operators apply calculations to the top elements.