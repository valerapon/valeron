#ifndef VARIABLE_H
#define VARIABLE_H

#include <iostream>
#include <stack>
#include <string>
#include <map>
#include "Lexem.h"

class Variable: public Lexem {
	static OBJECT _type;
	int _value;
	std::string _name;
public:
	Variable();
	Variable(std::string name);
	Variable(std::string name, int value);
	virtual OBJECT get_type() const;
	int get_value_from_table() const;
	virtual int get_value() const;
	virtual int get_priority() const;
	virtual std::string get_name() const;
	virtual void set_value(int value);
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

#endif
