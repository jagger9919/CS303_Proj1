#include "Evaluator.h"
#include <cctype>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

// Given an expression (string), evaluate if possible
double Evaluator::evalExp(const string& exp) {
	// Empty both stacks.
	while (!operators.empty())
		operators.pop();
	while (!values.empty())
		values.pop();

	// Begin evaluating the expression.
	// Initialize tokens.
	istringstream expTokens(exp);
	char nxtToken;

	// Keep reading the tokens. Evaluate each iteration.
	while (expTokens >> nxtToken) {
		if (isdigit(nxtToken)) {
			cout << "Pushing value.. (" << nxtToken << ")" << endl << endl;
			// Putback nxtToken so it can be re-read as a value.
			expTokens.putback(nxtToken);
			// Re-read, push value to value stack.
			double val;
			expTokens >> val;
			values.push(val);
		}

		else if (!isdigit(nxtToken)) {
			// Convert the operator to a string.
			string strOp(1, nxtToken);
			// Read next token, decide if it belongs to the operator being read.
			// Scenario 1: operator is !, <, or > 
			if (strOp == "!" || strOp == "<" || strOp == ">") {
				expTokens >> nxtToken;
				if (nxtToken == '=')
					strOp += "=";
				else
					expTokens.putback(nxtToken);
			}
			// Scenario 2: operator is |, &, =, -, or +
			else if (strOp == "|" || strOp == "&" || strOp == "=" || strOp == "-" || strOp == "+") {
				expTokens >> nxtToken;
				// Convert the operator to a string.
				// If the operators are the same, append to the operator. Else, put it back.
				string compStr(1, nxtToken);
				if (strOp == compStr)
					strOp += compStr;
				else
					expTokens.putback(nxtToken);
			}
			// Check to see if the operator is valid, process it.
			if (isOp(strOp)) {
				cout << "Processing operator.. (" << strOp << ")" << endl << endl;
				pushOp(strOp);
			}
			else
				throw "EXCEPTION: Unexpected character encountered.";
		}
	}

	// When finished evaluating the tokens, pop the remaining operators.
	// Finish evaluating values.
	while (!operators.empty()) {
		cout << "Evaluating.." << endl;
		cout << operators.top() << ", " << values.top();
		string op = operators.top(); operators.pop(); // Assign op as the top operator in stack, pop it.
		double rhs = values.top(); values.pop();    // Assign rhs as the top value in stack, pop it.
		if (op == "++" || op == "--" || op == "-") {
			if (precedence(op) == 8 && op == "-") {
				cout << " = " << evalOp(rhs, op);
				values.push(-1 * rhs);
			}
			else {
				cout << " = " << evalOp(rhs, op);
				values.push(evalOp(rhs, op));
			}
		}
		else {
			cout << ", " << values.top() << " = ";
			double lhs = values.top(); values.pop();    // Assign lhs as the top value in stack, pop it.
			cout << evalOp(rhs, lhs, op) << endl << endl;
			values.push(evalOp(rhs, lhs, op));
		}
	}

	return values.top();
}

// Process a given operator.
void Evaluator::pushOp(string op) {
	// If the operator stack is empty or the operator is an opening parenthesis, push it.
	// If the stack is empty and the operator is a closing paranthesis, throw an error.
	if (operators.empty() || op == "(" || op == "[" || op == "{") {
		if (op == ")" || op == "]" || op == "}")
			throw "EXCEPTION: Unmatched close parenthesis";
		operators.push(op);
	}
	else {
		if (precedence(op) > precedence(operators.top()))
			operators.push(op);
		else {
			// Pop all operators with >= precedence than op.
			// Evaluate, push values.
			while (!operators.empty()
				&& (operators.top() != "(")
				&& (operators.top() != "[")
				&& (operators.top() != "{")
				&& (precedence(op) <= precedence(operators.top()))) {
				cout << "Evaluating.. (Inside)" << endl;
				cout << operators.top() << ", " << values.top();
				string op = operators.top(); operators.pop(); // Assign op as the top operator in stack, pop it.
				double rhs = values.top(); values.pop();    // Assign rhs as the top value in stack, pop it.
				if (op == "++" || op == "--" || op == "-") {
					if (precedence(op) == 8 && op == "-") {
						cout << " = " << evalOp(rhs, op);
						values.push(-1 * rhs);
					}
					else {
						cout << " = " << evalOp(rhs, op);
						values.push(evalOp(rhs, op));
					}
				}
				else {
					if (values.empty())
						throw "\nEXCEPTION: Too many operators.";
					cout << ", " << values.top() << " = ";
					double lhs = values.top(); values.pop();    // Assign lhs as the top value in stack, pop it.
					cout << evalOp(rhs, lhs, op) << endl << endl;
					values.push(evalOp(rhs, lhs, op));
				}
			}

			// Assert: (The stack is empty) || (the op an opening paranthesis) || (op's prec > operators.top()'s prec)
			if (op == ")") {
				if (!operators.empty() && (operators.top() == "("))
					operators.pop();
				else
					throw "EXCEPTION: Unmatched close parentheses";
			}
			else if (op == "]") {
				if (!operators.empty() && (operators.top() == "["))
					operators.pop();
				else
					throw "EXCEPTION: Unmatched close parentheses";
			}
			else if (op == "}") {
				if (!operators.empty() && (operators.top() == "{"))
					operators.pop();
				else
					throw "EXCEPTION: Unmatched close parentheses";
			}
			else
				operators.push(op);
		}
	}
}

// Given the RHS, LHS, and Operator, return the expected result.
double Evaluator::evalOp(double rhs, double lhs, string op) {
	/// Basic Arithmatic
	// Addition
	if (op == "+") {
		return lhs + rhs;
	}
	// Subtraction
	if (op == "-") {
		return lhs - rhs;
	}
	// Multiplication
	if (op == "*") {
		return lhs * rhs;
	}
	// Division
	if (op == "/") {
		if (rhs == 0)
			throw "\nEXCEPTION: Cannot divide by zero.";
		return lhs / rhs;
	}
	// Modulus
	if (op == "%") {
		return 0; //FIXME
	}
	// Power
	if (op == "^") {
		int orig = lhs;
		for (int i = 1; i < rhs; i++)
			lhs *= orig;
		return lhs;
	}

	/// Logical Operators
	// OR
	if (op == "||")
		return lhs || rhs;
	// AND
	if (op == "&&")
		return lhs && rhs;
	// NOT
	if (op == "!")
		return 0;
	// Equal
	if (op == "==")
		return lhs == rhs;
	// Greater-Than
	if (op == ">")
		return lhs > rhs;
	// Greater-Than or Equal
	if (op == ">=")
		return lhs >= rhs;
	// Less-Than
	if (op == "<")
		return lhs < rhs;
	// Less-Than or Equal
	if (op == "<=")
		return lhs <= rhs;

	return 0;
}

// Given rhs & op, evaluate.
double Evaluator::evalOp(double rhs, string op) {
	// Negative
	if (op == "-")
		return -1 * rhs;
	/// Increment / Decrement
	// Prefix Inc
	if (op == "++")
		return ++rhs;
	// Prefix Dec
	if (op == "--")
		return --rhs;
}

// Return true if the operator is valid. Else, return false.
bool Evaluator::isOp(string op) {
	for (int i = 0; i < 24; i++) {
		string compOp = OPERATORS[i];
		if (op == compOp)
			return true;
	}
	return false;
}

// Return the precedence of an operator.
int Evaluator::precedence(string op) {
	int retVal = -1;
	for (int i = 0; i < 24; i++)
		if (op == OPERATORS[i]) {
			retVal = PRECEDENCE[i];
			break;
		}
	return retVal;
}
