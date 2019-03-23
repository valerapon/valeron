#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include "Lexem.h"
#include "Number.h"
#include "Operator.h"
#include "Variable.h"
#include "Label.h"
#include "Array.h"
#include "Function.h"
#include "Algorithm.h"

std::vector<std::vector<Lexem *>> main_poliz;
extern std::map<std::string, Label *> table_label;
extern std::map<std::string, Function *> table_function;
extern std::stack<Function *> stack_function;
int cur_row, cur_col;

int main() {
	std::vector<Lexem *> infix, postfix;
	std::string str;
	std::stack<Condition *> condition_stack;
	int row, col;
	Algorithm alg;
	//create poliz table
	while (std::getline(std::cin, str)) {
		if (str.size() == 0) {
			continue;
		}
		if (str == "end") {
			break;
		}
		infix = alg.parse_lexem(str);
		main_poliz.push_back(alg.build_poliz(infix));
		//main_poliz.push_back(build_poliz(infix));
	}
	//define labels
	/*
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			if (main_poliz[i][j] -> get_type() == LABEL) {
				new Label(main_poliz[i][j] -> get_name(), i, j);
			}
		}
	}*/
	alg.defineLabels();
	//define condition and loop
	/*
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			if (main_poliz[i][j] -> get_type() == IF){
				delete main_poliz[i][j];
				If *tmp = new If;
				main_poliz[i][j] = tmp;
				condition_stack.push(tmp);
			}
			else if (main_poliz[i][j] -> get_type() == ELSE) {
				if (condition_stack.top() -> get_type() != IF) {
					std::cout << "Before else not if " << i << " and " << j << std::endl;
					exit(0);
				}
				delete main_poliz[i][j];
				Else *tmp = new Else;
				main_poliz[i][j] = tmp;
				condition_stack.push(tmp);
			}
			else if (main_poliz[i][j] -> get_type() == WHILE) {
				While *tmp = new While(main_poliz[i][j] -> get_value());
				delete main_poliz[i][j];
				main_poliz[i][j] = tmp;
				condition_stack.push(tmp);

			}
			else if (main_poliz[i][j] -> get_type() == FLBRACKET) {
				if (condition_stack.top() -> get_type() == IF || condition_stack.top() -> get_type() == ELSE || condition_stack.top() -> get_type() == WHILE) {
					if (condition_stack.top() -> get_pos_start().first == -1) {
						condition_stack.top() -> set_pos_start(std::pair<int, int>(i, j));
					}
					else {
						std::cout << "Too much '{' on " << i << " and " << j << std::endl;
						exit(0);
					}
				}
			}
			else if (main_poliz[i][j] -> get_type() == FRBRACKET) {
				if (condition_stack.top() -> get_type() == IF || condition_stack.top() -> get_type() == ELSE || condition_stack.top() -> get_type() == WHILE) {
					if (condition_stack.top() -> get_pos_start().first == -1) {
						std::cout << "Not enough '{' " << i << " and " << j << std::endl;
						exit(0);
					}
					if (condition_stack.top() -> get_pos_end().first == -1) {
						condition_stack.top() -> set_pos_end(std::pair<int, int>(i, j));
					}
					else {
						std::cout << "Too much '}' " << i << " and " << j << std::endl;
						exit(0);
					}
					if (condition_stack.top() -> get_type() == WHILE) {
						Goto *tmp = new Goto("$while" + std::to_string(condition_stack.top() -> get_value()));
						main_poliz[i].insert(main_poliz[i].begin() + j + 1, tmp);
						condition_stack.pop();
						continue;
					}
					if (condition_stack.top() -> get_type() == ELSE) {
						Condition *tmp = condition_stack.top();
						condition_stack.pop();
						if (condition_stack.top() -> get_pos_start().first == -1 || 
						    condition_stack.top() -> get_pos_end().first == -1) {
							std::cout << "Not enough '{' or '}' " << i << " and " << j << std::endl;
							exit(0);
						}
						else {
							condition_stack.top() -> set_else_ptr(tmp);
							condition_stack.pop();
						}
					}
				}
			}
		}
	}*/
	alg.defineConditionsAndLoops();
	//define function
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			if (main_poliz[i][j] -> get_type() == FUNCTION && main_poliz[i][j] -> is_definition()) {
				Function *new_function = new Function(main_poliz[i][j] -> get_name(), main_poliz[i][j] -> get_arguments(),
								      main_poliz[i][j] -> is_definition());
				if (table_function.find(new_function -> get_name()) != table_function.end()) {
					std::cout << "So mane same functions" << std::endl;
					exit(0);
				}
				new_function -> set_define_position(std::pair<int, int>(i, j));
				table_function.insert(std::pair<std::string, Function *>(new_function -> get_name(), new_function));
			}
		}
	}
	//print poliz table
	std::cout << "poliz:" << std::endl;
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			main_poliz[i][j] -> print();
		}
		std::cout << std::endl;
	}
	//evaluate poliz and print result
	std::cout << "result:" << std::endl;
	//evaluate_poliz();
	alg.evaluate_poliz();
	//print variable table
	std::cout << "\nvariable:" << std::endl;
	for (std::map<std::string, Variable *>::const_iterator i = table.begin(); i != table.end(); ++i) {
		std::cout << i -> first << '=' << i -> second -> get_value() << std::endl;
	}
	//print label table
	std::cout << "label:" << std::endl;
	for (std::map<std::string, Label *>::const_iterator i = table_label.begin(); i != table_label.end(); ++i) {
		std::cout << i -> first << std::endl;
	}
	//print array table
	std::cout << "array:" << std::endl;
	for (std::map<std::string, Array *>::const_iterator i = stack_function.top() -> _table_array.begin(); i != stack_function.top() -> _table_array.end(); ++i) {
		i -> second -> print_elements();
		std::cout << std::endl;
	}
	//print function table
	std::cout << "function:" <<std::endl;
	for (std::map<std::string, Function *>::const_iterator i = table_function.begin(); i != table_function.end(); ++i) {
		i -> second -> print();
		for (std::map<std::string, Variable *>::const_iterator j = i -> second -> _table_variable.begin(); j != i -> second -> _table_variable.end(); ++j) {
			j -> second -> print();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	return 0;
}
