#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include "Evaluator.h"
using namespace std;

/*
TO-DO:
~ MAKE AN EXCEPTION FOR WHEN THERE'S TWO OPERATORS IN A ROW
~ IMPLEMENT INCREMENT/DECREMENT
~ IMPLEMENT NEGATIVE
*/

int main() {
	Evaluator evalMe;
	string equation = "((1+1*3)^2 == 16) && ( 1 * 0 == 0)";

	// Given the equation above, find its result.
	try {
		double result = evalMe.evalExp(equation);
		cout << endl << "RESULT: [ " << equation << " ] = " << result << endl;
		
	}
	
	// Inform the user if they encounter an exception.
	catch (const char* error) {
		cout << endl << error << endl;
	}

	system("pause");
}
