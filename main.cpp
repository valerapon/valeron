#include "headers/Algorithm.h"

int main(int argc, char **argv) {
	try {
		Algorithm alg;
		alg.definePoliz();
		alg.defineLabels();
		alg.defineConditionsAndLoops();
		alg.defineFunctions();
		alg.evaluate_poliz();
		if (argv[1] == "-debug") {
			alg.printPolizTable();
			alg.printVariableTable();
			alg.printArrayTable();
			alg.printLabelTable();
			alg.printFunctionTable();
		}
		alg.deleteData();
	}
	catch(...) {
		error();
	}
	return 0;
}
