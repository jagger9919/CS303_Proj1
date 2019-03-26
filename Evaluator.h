#pragma once
#include <string>
#include <stack>
using namespace std;

class Evaluator {
private:
	// Initialize stack of operators and values.
	stack<double> values;
	stack<string> operators;

	// Initialize valid operators and their corresponding precedences
	const string OPERATORS[24] = { "(", ")", "{", "}", "[", "]", "||", "&&", "==", "!=", ">", ">=", "<", "<=", "+", "-", "*", "/", "%", "^", "-", "--", "++", "!" };
	const int PRECEDENCE[24] = { -1, -1, -1, -1, -1, -1, 1, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 8 };
public:
	int Count = 0;
	int getCount();
	// Given an expression (string), evaluate if possible.
	double evalExp(const string& exp);

	// Returns true if the given char is an operator.
	bool isOp(string op);

	// Handles the pushing of operators.
	void pushOp(string op);

	// Returns the corresponding precedence of an operator.
	int precedence(string op);

	// Given rhs & lhs & op, evaluate.
	double evalOp(double rhs, double lhs, string op);
};

