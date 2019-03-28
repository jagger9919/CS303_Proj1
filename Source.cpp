#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>
#include "Evaluator.h"
using namespace std;

int main() {
	Evaluator evalMe;
	string equation = "++ ++ 2 - 5 * (3 ^ 2)";

	// Given the equation above, find its result.
	try {
		double result = evalMe.evalExp(equation);
		cout << endl << "RESULT: [ " << equation << " ] = " << result << endl;

	}

	// Inform the user if they encounter an exception.
	catch (const char* error) {
		cout << endl << error << " @ char: " << evalMe.getCount() << endl;
	}

	system("pause");
}
