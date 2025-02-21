# Equation-Evaluator
A calculator system that reads, validates, and evaluates equations from an input file.

## Summary
This project implements a calculator system that processes mathematical equations written in infix notation from an input file. The program reads an unspecified number of equations, checks their validity, converts valid equations to prefix notation, evaluates them, and provides detailed output.

## Specifications
This application should be able to perform the following tasks:
1. **Read** the input file containing equations. The user should provide the name of the input file.
2. **Validate** equations (check if they are valid or not). The output should indicate:
   - Example:
     - Equation No. 1 → Valid
     - Equation No. 2 → Invalid: Missing operator between `4[6`
     - Equation No. 3 → Invalid: Parenthesis `(` is not closed
     - Equation No. 4 → Valid
3. **Convert** valid equations from infix to prefix notation and print the prefix expressions.
4. **Evaluate** the prefix expressions and print the results of each equation:
   - Example:
     - Equation No. 1 → 75
     - Equation No. 4 → 4
5. **Print invalid equations**, listing all invalid equations from the input file.
6. **Save results to an output file** (`output.txt`), indicating for each input equation whether it is valid or not. If valid, it should include the prefix expression and its result.
7. **Exit** the program gracefully.

## Author
Qusay Taradeh

