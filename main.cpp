#include "headers/Algorithm.h"

int main(int argc, char **argv) {
	try {
		Algorithm alg;
		alg.definePoliz();
		alg.defineLabels();
		alg.defineConditionsAndLoops();
		alg.defineFunctions();
		alg.evaluate_poliz();
		if (argc > 1 && argv[1][0] == '-' && argv[1][1] == 'd') {
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
