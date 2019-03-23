#include "Algorithm.h"

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
	}
	catch(...) {
		error();
	}
	return 0;
}
