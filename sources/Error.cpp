#include <iostream>
#include "../headers/Error.h"

void error() {}

void errorInput(int col) {
	std::cout << "Error of input: ";
	throw col;
}

void errorNoGotoTarget(int col) {
	std::cout << "No goto target: ";
	throw col;
}

void errorNoDefTarget(int col) {
	std::cout << "No def target: ";
	throw col;
}

void errorFunctionName(int col) {
	std::cout << "Incorrect function name: ";
	throw col;
}

void errorFunctionArgument(int col) {
	std::cout << "Incorrect function argument: ";
	throw col;
}

void errorNumberBuild(int col) {
	std::cout << "Number can't include non-digit symbols: ";
	throw col;
}

void errorWordFirstSymbol(int col) {
	std::cout << "Name of object can't start of digit: ";
	throw col;
}

void errorSimillarLabels(int row, int col) {
	std::cout << "Too many simillar labels: " << row << ' ' << col << std::endl;
	throw 0;
}

void errorElseLogic(int row) {
	std::cout << "Too many else, too few if: " << row << std::endl;
	throw row;
}

void errorFBracketCount(int row) {
	std::cout << "Error of { and } count: " << row << std::endl;
	throw row;
}

void errorConditionLogic() {
	std::cout << "Error of condition logic" << std::endl;
	throw 0;
}

void errorSimillarFunctions(int row, int col) {
	std::cout << "Too many simillar functions: " << row << ' ' << col << std::endl;
	throw 0;
}

void errorTypeCompatibility(int col) {
	std::cout << "Error of type compatibility: ";
	throw col;
}

void errorOperation(char op1, char op2) {
	std::cout << "Incorrect operand of '" << op1 << op2 << "\': ";
	throw 0;
}

void errorFunctionNotFound() {
	std::cout << "Function not found: ";
	throw 0;
}

void errorFewArguments() {
	std::cout << "Few function arguments: ";
	throw 0;
}

void errorEqualFunctionArguments() {
	std::cout << "Equal function arguments: ";
	throw 0;
}
