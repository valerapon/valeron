#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "Lexem.h"
#include "Label.h"

std::map<std::string, Label *> table_label;

OBJECT Label::_type = LABEL;

Label::Label() {}

Label::Label(std::string name) {
	_name = name;
}

Label::Label(std::string name, int row, int col) {
	_row = row;
	_col = col;
	_name = name;
}

int Label::get_row() const {
	return _row;
}

int Label::get_col() const {
	return _col;
}

int Label::get_value() const {
	return 0;
}

OBJECT Label::get_type() const {
	return _type;
}

int Label::get_priority() const {
	return PRIORITY[_type];
}

std::string Label::get_name() const {
	return _name;
}

void Label::stack_evaluate(std::stack<Lexem *> &stack) const {}

void Label::print() const {
	std::cout << _name << ':';
}
