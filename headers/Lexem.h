#ifndef LEXSEM_H
#define LEXSEM_H

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "Error.h"

enum OBJECT {
	NONE,
	LABEL, IF, ELSE, WHILE,
	ASSIGN,
	RLBRACKET, RRBRACKET,
	LBRACKET, RBRACKET, FLBRACKET, FRBRACKET,
	AND,
	OR,
	XOR,
	BITAND,
	BITOR,
	BITXOR,
	EQ, NEQ,
	LEQ, LT, GEQ, GT,
	BLS, BRS,
	PLUS, MINUS,
	MULTIPLY, DIVISION, MOD,
	GOTO, PRINT, NEWLINE,
	VARIABLE, NUMBER, ARRAY, FUNCTION,
	RETURN, COMMA, ENDFUNCTION
};

extern int PRIORITY[];

class Lexem {
public:
	Lexem();
	virtual OBJECT get_type() const = 0;
	virtual int get_value() const = 0;
	virtual int get_priority() const = 0;
	virtual int get_index() const;
	virtual int get_size() const;
	virtual std::string get_name() const = 0;
	virtual void set_value(int value);
	virtual void set_index(int index);
	virtual std::vector<int> get_data() const;
	virtual int get_argument_count() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const = 0;
	virtual std::vector<std::string> get_arguments() const;
	virtual bool is_definition() const;
	virtual void print() const = 0;
};

#endif
