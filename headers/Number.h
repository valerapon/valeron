#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
#include <stack>
#include <string>
#include "Lexem.h"

class Number: public Lexem {
	static OBJECT _type;
	int _value;
public:
	Number();
	Number(int number);
	virtual int get_value() const;
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual std::string get_name() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

#endif
