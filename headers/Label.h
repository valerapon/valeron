#ifndef LABEL_H
#define LABEL_H

#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "Lexem.h"

class Label: public Lexem {
	int _row, _col;
	static OBJECT _type;
	std::string _name;
public:
	Label();
	Label(std::string name);
	Label(std::string name, int row, int col);
	int get_row() const;
	int get_col() const;
	virtual int get_value() const;
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual std::string get_name() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

extern std::map<std::string, Label *> table_label;

#endif
