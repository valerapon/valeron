#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include "Lexem.h"
#include "Variable.h"
#include "Array.h"

class Function: public Lexem {
    	static OBJECT _type;
    	std::string _name;
    	bool _is_definition;
    	std::pair<int, int> _define_position;
	std::pair<int, int> _start_position;
public:
    	std::map<std::string, Variable *> _table_variable;
    	std::map<std::string, Array *> _table_array;
    	std::stack<Lexem *> _stack;
    	std::vector<std::string> _arguments;

	Function();
	Function(std::string name, bool is_definition);
	Function(std::string name, std::vector<std::string> arguments, bool is_definition);
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual int get_value() const;
	virtual std::string get_name() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual int get_argument_count() const;
	virtual std::vector<std::string> get_arguments() const;
	virtual bool is_definition() const;
	std::pair<int, int> get_define_position() const;
	std::pair<int, int> get_start_position() const;
	void set_define_position(std::pair<int, int> position);
	void set_start_position(std::pair<int, int> position);
	virtual void print() const;
};

extern std::map<std::string, Function *> table_function;

#endif
