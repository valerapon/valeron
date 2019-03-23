#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include "Function.h"

OBJECT Function::_type = FUNCTION;

std::map<std::string, Function *> table_function;
std::stack<Function *> stack_function;
extern std::vector<std::vector<Lexem *>> main_poliz;
extern std::map<std::string, Array *> table_array;
extern int cur_row, cur_col;

Function::Function() {}

Function::Function(std::string name, bool is_definition) {
	_name = name;
	_is_definition = is_definition;
}

Function::Function(std::string name, std::vector<std::string> arguments, bool is_definition) {
    _name = name;
    _arguments = arguments;
    _is_definition = is_definition;
}

OBJECT Function::get_type() const {
    return _type;
}

int Function::get_priority() const {
    return PRIORITY[_type];
}

int Function::get_value() const {
    return 0;
}

std::string Function::get_name() const {
    return _name;
}

void Function::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (_is_definition) {
		int function_counter = 1, i = cur_row, j = cur_col + 1;
		for (; i < main_poliz.size(); ++i) {
			for (; j < main_poliz[i].size(); ++j) {
				if (main_poliz[i][j] -> get_type() == FUNCTION && main_poliz[i][j] -> is_definition()) {
					++function_counter;
				}
				if (main_poliz[i][j] -> get_type() == ENDFUNCTION) {
					--function_counter;
				}
				if (function_counter == 0) {
					cur_row = i;
					cur_col = j;
					return;
				}
			}
			j = 0;
		}
	}
	if (table_function.find(_name) == table_function.end()) {
		errorFunctionNotFound();
	}
	std::vector<std::string> arg = table_function[_name] -> _arguments;
	Function *new_func = new Function(_name, arg, true);
	for (int i = 0; i < arg.size(); ++i) {
		if (stack.empty()) {
			errorFewArguments();
		}
		Lexem *tmp = stack.top();
		if (tmp -> get_type() == NUMBER || tmp -> get_type() == VARIABLE) {
			if (new_func -> _table_variable.find(arg[arg.size() - i - 1]) != new_func -> _table_variable.end()) {
				errorEqualFunctionArguments();
			}
			new_func -> _table_variable.insert(std::pair<std::string, Variable *>(arg[arg.size() - i - 1],
											     new Variable(arg[arg.size() - i - 1],
												          tmp -> get_value())));
		}
		else if (tmp -> get_type() == ARRAY) {
			if (new_func -> _table_array.find(arg[arg.size() - i - 1]) != new_func -> _table_array.end()) {
				errorEqualFunctionArguments();
			}
			new_func -> _table_array.insert(std::pair<std::string, Array *>(arg[arg.size() - i - 1],
											  new Array(arg[arg.size() - i - 1],
												    tmp -> get_data())));
		}
		stack.pop();
	}
	new_func -> set_start_position(std::pair<int, int>(cur_row, cur_col));
	stack_function.push(new_func);
	cur_row = table_function[_name] -> _define_position.first;
	cur_col = table_function[_name] -> _define_position.second + 1;
}

void Function::print() const {
    std::cout << _name << "( ";
    for (int i = 0; i < _arguments.size(); ++i) {
    	std::cout << _arguments[i] << ' ';
    }
    std::cout << ')';
}

int Function::get_argument_count() const {
    return _arguments.size();
}

std::vector<std::string> Function::get_arguments() const {
	return _arguments;
}

bool Function::is_definition() const {
	return _is_definition;
}

std::pair<int, int> Function::get_define_position() const {
	return _define_position;
}

std::pair<int, int> Function::get_start_position() const {
	return _start_position;
}

void Function::set_define_position(std::pair<int, int> position) {
	_define_position = position;
}

void Function::set_start_position(std::pair<int, int> position) {
	_start_position = position;
}

