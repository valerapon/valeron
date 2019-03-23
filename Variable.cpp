#include <iostream>
#include <stack>
#include <string>
#include <map>
#include "Variable.h"
#include "Function.h"

extern std::stack<Function *> stack_function;
OBJECT Variable::_type = VARIABLE;

Variable::Variable() {}

Variable::Variable(std::string name) {
	_name = name;
}

Variable::Variable(std::string name, int value) {
	_name = name;
	_value = value;
}

OBJECT Variable::get_type() const {
	return _type;
}

int Variable::get_value_from_table() const {
	return _value;
}

int Variable::get_value() const {
	if (stack_function.top() -> _table_variable.find(_name) == stack_function.top() -> _table_variable.end()) {
		stack_function.top() -> _table_variable.insert(std::pair<std::string, Variable *>(_name, new Variable(_name, 0)));
		return 0;
	}
	return stack_function.top() -> _table_variable[_name] -> get_value_from_table();
}

std::string Variable::get_name() const {
	return _name;
}

int Variable::get_priority() const {
	return PRIORITY[get_type()];
}

void Variable::set_value(int value) {
	_value = value;
}

void Variable::stack_evaluate(std::stack<Lexem *> &stack) const {
	stack.push(new Variable(get_name(), 1));	
}

void Variable::print() const {
	std::cout << _name << ' '; //<< table[_name] -> get_value();
}

