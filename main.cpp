#include "headers/Algorithm.h"

int main() {
	try {
		Algorithm alg;
		alg.definePoliz();
		alg.defineLabels();
		alg.defineConditionsAndLoops();
		alg.defineFunctions();
		alg.evaluate_poliz();
		alg.printPolizTable();
		alg.printVariableTable();
		alg.printArrayTable();
		alg.printLabelTable();
		alg.printFunctionTable();
		alg.deleteData();
	}
	catch(...) {
		error();
	}
	return 0;
}
