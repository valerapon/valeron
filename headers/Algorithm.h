#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include "Lexem.h"
#include "Number.h"
#include "Operator.h"
#include "Variable.h"
#include "Label.h"
#include "Array.h"
#include "Function.h"

class Algorithm {
	static int whileCounter;
public:
	bool isDigit(char ch);
	bool isSymbol(char ch);
	bool isPass(char ch);
	bool isTypeCompatibility(OBJECT now, OBJECT pre);
	void addGoto(std::vector<Lexem *> &listLex, std::string &string, int &i);	
	void addIf(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addElse(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addWhile(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addPrint(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addNewline(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addReturn(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addDef(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addEndef(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addNumber(std::vector<Lexem *> &listLex, std::string &string, int &i);
	void addWord(std::vector<Lexem *> &listLex, std::string &string, int &i);
	std::vector<Lexem *> parse_lexem(std::string &string);
	std::vector<Lexem *> build_poliz(std::vector<Lexem *> infix);
	int evaluate_poliz();
	void definePoliz();
	void defineLabels();
	void defineConditionsAndLoops();
	void defineFunctions();
	void printLine();
	void printPolizTable();
	void printVariableTable();
	void printLabelTable();
	void printArrayTable();
	void printFunctionTable();
	void deleteData();
};

#endif
