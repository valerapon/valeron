#include <iostream>
#include <stack>
#include <string>
#include "Lexem.h"
#include "Number.h"


OBJECT Number::_type = NUMBER;

Number::Number() {
	_value = 1;
}

Number::Number(int number) {
	_value = number;
}

OBJECT Number::get_type() const {
	return _type;
}

int Number::get_value() const {
	return _value;
}

int Number::get_priority() const {
	return PRIORITY[get_type()];
}

std::string Number::get_name() const {
	int tmp = _value;
	std::string name = "", empty = "";
	do {
		name = std::to_string(tmp % 10) + name;
		tmp /= 10;
	} while (tmp);
	return name;
}

void Number::stack_evaluate(std::stack<Lexem *> &stack) const {
	stack.push(new Number(get_value()));
}

void Number::print() const {
	std::cout << _value;
}
