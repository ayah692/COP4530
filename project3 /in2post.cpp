#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <iomanip>
#include "Stack.h"
using namespace std;
using namespace cop4530;

int precedence(const string& op);
string infix2Postfix(const string& infix);
string evaluatePostfix(const string& postfix); 

int main()
 {
    string input;
    cout << "Enter infix expression (\"exit\" to quit): " << std::endl;

    while (getline(cin, input)) {
        if (input == "exit") break;

        string postfix = infix2Postfix(input);
        cout << "Postfix expression: " << postfix << endl;

        if (postfix.find("Error") != string ::npos) {
            cout << "Postfix evaluation: " << postfix << endl;
        } else {
            string evaluationResult = evaluatePostfix(postfix);
            if (evaluationResult.find("Error") != string::npos) {
                cout << "Postfix evaluation: " << postfix << " = " << evaluationResult << endl;
            } else {
                cout << "Postfix evaluation: " << postfix << " = " << evaluationResult << endl;
           }
        }

        cout << "Enter infix expression (\"exit\" to quit): " << endl;
    }

    return 0;
}

int precedence(const string& op)
 {
    if (op == "+" || op == "-") 
        return 1;
    if (op == "*" || op == "/")
         return 2;
    return 0;
}


string infix2Postfix(const string& infix)
 {
    Stack<string> operatorStack;
    string postfix;
    int openParentheses = 0;

    istringstream iss(infix);
    string token;

    while (iss >> token){ // Check if the token is an operand (number or variable) 
        if (isalnum(token[0]))
        {
            postfix += token + " ";
        } else if (token == "(") 
        {
            operatorStack.push(token);
            openParentheses++;
        } else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                postfix += operatorStack.top() + " ";
                operatorStack.pop();
            }
            if (!operatorStack.empty()) {
                operatorStack.pop(); // Remove the '('
                openParentheses--;
            } else {
		return "  has mismatched parens!";
            }
        } else { // The token is an operator
            while (!operatorStack.empty() && precedence(operatorStack.top()) >= precedence(token)) {
                postfix += operatorStack.top() + " ";
                operatorStack.pop();
            }
            operatorStack.push(token);
        }
    }

    // Pop all the operators from the stack
    while (!operatorStack.empty()) {
        if (operatorStack.top() == "(") {
            return "Error: Infix expression: " + infix + " has mismatched parens!";
        }
        postfix += operatorStack.top() + " ";
        operatorStack.pop();
    }

     if (openParentheses != 0) {
       return "Error: Infix expression: " + infix + " has mismatched parens!";
    }

    return postfix;
}
string evaluatePostfix(const string& postfix) {
    Stack<double> operandStack;
    istringstream iss(postfix);
    string token;

    while (iss >> token) {
        if (isdigit(token[0])) { // Check if the token is a number
            operandStack.push(stod(token));
        } else if (isalpha(token[0])) { // Check if the token is a variable
            return postfix; // Return the postfix expression without evaluation
        } else { // The token is an operator
            if (operandStack.size() < 2) {
                return "Error: Missing operands in the expression";
            }
            double operand2 = operandStack.top(); operandStack.pop();
            double operand1 = operandStack.top(); operandStack.pop();

            if (token == "+") {
                operandStack.push(operand1 + operand2);
            } else if (token == "-") {
                operandStack.push(operand1 - operand2);
            } else if (token == "*") {
                operandStack.push(operand1 * operand2);
            } else if (token == "/") {
                if (operand2 == 0)
         return "Error: Division by zero";
                operandStack.push(operand1 / operand2);
            }
        }
    }

    if (operandStack.size() != 1) 
        {       
        return "Error: Missing operand in postfix string. Unable to evaluate postfix string!";
    }

    // Get the result
    double result = operandStack.top();

    ostringstream out;
    out << fixed << setprecision(0) << result; 
    return out.str();
}

