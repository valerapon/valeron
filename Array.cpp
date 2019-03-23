#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "Lexem.h"
#include "Array.h"
#include "Function.h"

OBJECT Array::_type = ARRAY;
std::map<std::string, Array *> table_array;
extern std::stack<Function *> stack_function;

Array::Array() {}

Array::Array(std::string name) {
	_name = name;
	_size = 0;
}

Array::Array(std::string name, std::vector<int> data) {
	_name = name;
	_data.resize(data.size());
	for (int i = 0; i < data.size(); ++i) {
		_data[i] = data[i];
	}
	_size = data.size();
}

OBJECT Array::get_type() const {
	return _type;
}

int Array::get_priority() const {
	return PRIORITY[_type];
}

std::string Array::get_name() const {
	return _name;
}

int Array::get_table_value(int index) {
	if (index + 1 > _size) {
		_data.resize(index + 1, 0);
		_size = index + 1;
		return 0;
	}
	return _data[index];
}

int Array::get_value() const {
	return stack_function.top() -> _table_array[_name] -> get_table_value(_index);
}

std::vector<int> Array::get_data() const {
	//std::cout << "MAYBE HERE?!?!?" << std::endl;
	return stack_function.top() -> _table_array[_name] -> _data;
}

void Array::set_table_value(int value, int index) {
	if (index + 1 > _size) {
		_data.resize(index + 1, 0);
		_size = index + 1;
	}
	_data[index] = value;
}

void Array::set_value(int value) {
	stack_function.top() -> _table_array[_name] -> set_table_value(value, _index);
}

void Array::set_index(int index) {
	_index = index;
}

int Array::get_size() const {
	return _size;
}

int Array::get_index() const {
	return _index;
}

void Array::stack_evaluate(std::stack<Lexem *> &stack) const {
	stack.push(new Array(get_name()));
}

void Array::print() const {
	std::cout << _name;
}

void Array::print_elements() const {
	std::cout << _name <<"[ ";
	for (std::vector<int>::const_iterator i = _data.begin(); i != _data.end(); ++i) {
		std::cout << *i<< ' ';
	}
	std::cout << ']';
}
