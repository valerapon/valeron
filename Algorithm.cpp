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

int Algorithm::whileCounter = 0;
std::vector<std::vector<Lexem *>> main_poliz;
extern std::map<std::string, Label *> table_label;
extern std::map<std::string, Function *> table_function;
extern std::stack<Function *> stack_function;
int cur_row, cur_col;

bool Algorithm::isDigit(char ch) {
	if (ch >= '0' && ch <= '9') {
		return true;
	}
	return false;
}

bool Algorithm::isSymbol(char ch) {
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_') {
		return true;
	}
	return false;
}

bool Algorithm::isPass(char ch) {
	if (ch == ' ' || ch == '\t' || ch == '\n') {
		return true;
	}
	return false;
}

bool Algorithm::isTypeCompatibility(OBJECT now, OBJECT pre) {
	if (now == pre && (now == NUMBER || now == VARIABLE || now == ARRAY)) {
		return false;
	}
	return true;
}

void Algorithm::addGoto(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 4;
	while (isPass(str[i])) {
		++i;
	}
	if (str[i] == '\0') {
		errorNoGotoTarget(i);
	}
	std::string obj = "";
	while (isSymbol(str[i]) || isDigit(str[i])) {
		obj += str[i];
			++i;
	}
	if (obj == "") {
		errorNoGotoTarget(i);
	}
	--i;
	listLex.push_back(new Goto(obj));

}

void Algorithm::addIf(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 2;
	listLex.push_back(new If);
}

void Algorithm::addElse(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 4;
	listLex.push_back(new Else);
}

void Algorithm::addWhile(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 5;
	Label *ptr = new Label("$while" + std::to_string(whileCounter));
	listLex.push_back(ptr);
	listLex.push_back(new While(whileCounter));
	++whileCounter;
}

void Algorithm::addPrint(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 5;
	listLex.push_back(new Print);
}

void Algorithm::addNewline(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 7;
	listLex.push_back(new New_Line);
}

void Algorithm::addReturn(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 6;
	listLex.push_back(new Return);
}

void Algorithm::addDef(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 3;
	while (isPass(str[i])) {
        	++i;
	}
	if (!isSymbol(str[i])) {
		errorNoDefTarget(i);
	}
	std::string obj = "";
	while (str[i] != '(') {
		if(!isSymbol(str[i]) && !isDigit(str[i])) {
			errorFunctionName(i);
		}
		obj += str[i];
		++i;
	}
	if (obj == "") {
		errorFunctionName(i);
	}
	++i;
	while (isPass(str[i])) {
	        ++i;
	}
	std::string arg_name;
	std::vector<std::string> arguments;
	while (str[i] != ')') {
		arg_name = "";
		bool isFirstSymbol = true;
		while (str[i] != ',' && str[i] != ')') {
			if (isPass(str[i])) {
				++i;
				continue;
			}
			if (isFirstSymbol && isDigit(str[i])) {
				errorFunctionArgument(i);
			}
			else {
				isFirstSymbol = false;
			}
			if (!isSymbol(str[i]) && !isDigit(str[i])) {
				errorFunctionArgument(i);
			}
			arg_name += str[i];
			++i;
		}
		if (arg_name == "") {
			errorFunctionArgument(i);
		}
		if (str[i] == ',') {
			++i;
		}
		arguments.push_back(arg_name);
	}
	listLex.push_back(new Function(obj, arguments, true));
}

void Algorithm::addEndef(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	i += 5;
	listLex.push_back(new EndFunction());
}

void Algorithm::addNumber(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	std::string obj = "";
	while (isDigit(str[i])) {
		obj += str[i];
		++i;
	}
	if (isSymbol(str[i])) {
		errorNumberBuild(i);
	}
	--i;
	listLex.push_back(new Number(stoi(obj)));
}

void Algorithm::addWord(std::vector<Lexem *> &listLex, std::string &str, int &i) {
	std::string obj = "";
	if (isDigit(str[i])) {
		errorWordFirstSymbol(i);
	}
	while (isSymbol(str[i]) || isDigit(str[i])) {
		obj += str[i];
		++i;
	}
	if (str[i] == ':') {
		listLex.push_back(new Label(obj));	
	} else if (str[i] == '[') {
		listLex.push_back(new Array(obj));
		listLex.push_back(new RLBracket());
	} else if (str[i] == '(') {
		listLex.push_back(new Function(obj, false));
		listLex.push_back(new LBracket());
	} else {
		--i;
		listLex.push_back(new Variable(obj));
	}
}

std::vector<Lexem *> Algorithm::parse_lexem(std::string &string) {
	std::vector<Lexem *> list_lex;
	OBJECT preLex = NONE;
	for (int i = 0; i < string.size(); ++i) {
		if (isPass(string[i])) {
			continue;
		} else if (string.substr(i, 4) == "goto") {
			addGoto(list_lex, string, i);
		} else if (string.substr(i, 2) == "if") {
			addIf(list_lex, string, i);
		} else if (string.substr(i, 4) == "else") {	
			addElse(list_lex, string, i);
		} else if (string.substr(i, 5) == "while") {	
			addWhile(list_lex, string, i);
		} else if (string.substr(i, 5) == "print") {	
			addPrint(list_lex, string, i);
		} else if (string.substr(i, 7) == "newline") {	
			addNewline(list_lex, string, i);
		} else if (string.substr(i, 6) == "return") {	
			addReturn(list_lex, string, i);
		} else if (string.substr(i, 3) == "def") {	
			addDef(list_lex, string, i);
		} else if (string.substr(i, 5) == "endef") {	
			addEndef(list_lex, string, i);
		} else if (isDigit(string[i])) {	
			addNumber(list_lex, string, i);
		} else if (isSymbol(string[i])) {	
			addWord(list_lex, string, i);
		} else if (string[i] == ',') {
			list_lex.push_back(new Comma);
		} else if (string[i] == '{') {
			list_lex.push_back(new FLBracket);
		} else if (string[i] == '}') {
			list_lex.push_back(new FRBracket);
		} else if (string[i] == '[') {
			list_lex.push_back(new RLBracket);
		} else if (string[i] == ']') {
			list_lex.push_back(new RRBracket);
		} else if (string[i] == '+') {
			list_lex.push_back(new Plus);
		} else if (string[i] == '-') {
			list_lex.push_back(new Minus);
		} else if (string[i] == '*') {
			list_lex.push_back(new Multiply);
		} else if (string[i] == '%') {
			list_lex.push_back(new Mod);
		} else if (string[i] == '/') {	
			list_lex.push_back(new Division);
		} else if (string[i] == '(') {	
			list_lex.push_back(new LBracket);
		} else if (string[i] == ')') {	
			list_lex.push_back(new RBracket);
		} else if (string[i] == '=') {
			if (string[i + 1] == '=') {
				list_lex.push_back(new Equally);
				++i;
			}
			else {
				list_lex.push_back(new Assign);
			}
		} else if (string[i] == '!' && string[i + 1] == '=') {
			list_lex.push_back(new Not_Equally);
			++i;
		} else if (string[i] == '<') {
			if (string[i + 1] == '=') {
				list_lex.push_back(new Less_or_Equally);
				++i;
			} else if (string[i + 1] == '<') {
				list_lex.push_back(new Bit_Shift_Left);
				++i;
			} else {
				list_lex.push_back(new Less);
			}
		} else if (string[i] == '>') {
			if (string[i + 1] == '=') {
				list_lex.push_back(new Greater_or_Equally);
				++i;
			} else if (string[i + 1] == '>') {
				list_lex.push_back(new Bit_Shift_Right);
				++i;
			} else {
				list_lex.push_back(new Greater);
			}
		} else if (string[i] == '&') {
			list_lex.push_back(new Bit_And);
		} else if (string[i] == '|') {
			list_lex.push_back(new Bit_Or);
		} else if (string[i] == '^') {
			list_lex.push_back(new Bit_Xor);
		} else {
			errorInput(i);
		}
		if (!isTypeCompatibility(list_lex[list_lex.size() - 1] -> get_type(), preLex)) {
			errorTypeCompatibility(i);
		}
		preLex = list_lex[list_lex.size() - 1] -> get_type();
	}
	return list_lex;
}

std::vector<Lexem *> Algorithm::build_poliz(std::vector<Lexem *> infix) {
	std::vector<Lexem *> poliz;
	std::stack<Lexem *> stack;
	for (int i = 0; i < infix.size(); ++i) {
		if (infix[i] -> get_type() == NUMBER) {
			poliz.push_back(infix[i]);
		} else if (infix[i] -> get_type() == VARIABLE) {
			poliz.push_back(infix[i]);
		} else if (infix[i] -> get_type() == ARRAY) {
			poliz.push_back(infix[i]);
		} else if (infix[i] -> get_type() == FLBRACKET || infix[i] -> get_type() == FRBRACKET) {
			while (!stack.empty()) {
				poliz.push_back(stack.top());
				stack.pop();
			}
			poliz.push_back(infix[i]);
		} else if (infix[i] -> get_type() == COMMA) {
			while(stack.top() -> get_type() != LBRACKET) {
				poliz.push_back(stack.top());
				stack.pop();
			}
		} else if (infix[i] -> get_type() == LABEL) {
			while (!stack.empty()) {
				poliz.push_back(stack.top());
				stack.pop();
			}
			poliz.push_back(infix[i]);
		} else if (!stack.empty()) {
			if (infix[i] -> get_type() == RLBRACKET) {
				stack.push(infix[i]);
			} else if (infix[i] -> get_type() == RRBRACKET) {
				while (stack.top() -> get_type() != RLBRACKET) {
					poliz.push_back(stack.top());
					stack.pop();
				}
				poliz.push_back(stack.top());
				stack.pop();
			} else if (infix[i] -> get_type() == LBRACKET) {
						stack.push(infix[i]);
			} else if (infix[i] -> get_type() == RBRACKET) {
				while (stack.top() -> get_type() != LBRACKET) {
					poliz.push_back(stack.top());
					stack.pop();
				}
				stack.pop();
			} else if (infix[i] -> get_type() == ASSIGN && stack.top() -> get_type() == ASSIGN) {
				stack.push(infix[i]);
			} else if (stack.top() -> get_type() != LBRACKET && stack.top() -> get_priority() >= infix[i] -> get_priority()) {
				while (!stack.empty() && stack.top() -> get_type() != LBRACKET && stack.top() -> get_priority() >= infix[i] -> get_priority()) {
					poliz.push_back(stack.top());
					stack.pop();
				}
				stack.push(infix[i]);
			} else {
				stack.push(infix[i]);
			}
		}
		else {
			stack.push(infix[i]);
		}
	}
	while (!stack.empty()) {
		poliz.push_back(stack.top());
		stack.pop();
	}
	return poliz;
}

int Algorithm::evaluate_poliz() {
	printLine();
	std::cout << "result:" << std::endl;
	cur_row = 0;
	Function *main = new Function("main", false);
	stack_function.push(main);
	try {
		while (cur_row < main_poliz.size()) {
			cur_col = 0;
			while (cur_col < main_poliz[cur_row].size()) {
				main_poliz[cur_row][cur_col] -> stack_evaluate(stack_function.top() -> _stack);
				++cur_col;
			}
			++cur_row;
		}
	}
	catch (int tmp) {
		std::cout << cur_row << ' ' << cur_col <<std::endl;
		throw 0;
	}
	catch(...) {
		throw 0;
	}
	std::cout << std::endl;
	return 0;
}

void Algorithm::definePoliz() {
	std::string str;
	int row = 0;
	try {
		while (std::getline(std::cin, str) && str != "end") {
			if (str.size() == 0) {
				++row;
				continue;
			}
			main_poliz.push_back(build_poliz(parse_lexem(str)));
			++row;
		}
	}
	catch (int col) {
		std::cout << row << ", " << col << std::endl;
		throw "error";
	}
	catch (...) {
		throw "error";
	}
}

void Algorithm::defineLabels() {
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			if (main_poliz[i][j] -> get_type() == LABEL) {
				if (table_label.find(main_poliz[i][j] -> get_name()) != table_label.end()) {
					errorSimillarLabels(i, j);
				}
				table_label.insert(std::pair<std::string, Label *>(main_poliz[i][j] -> get_name(), new Label(main_poliz[i][j] -> get_name(), i, j)));
			}
		}
	}
}

void Algorithm::defineConditionsAndLoops() {
	std::stack<Condition *> condition_stack;
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			if (main_poliz[i][j] -> get_type() == IF){
				delete main_poliz[i][j];
				If *tmp = new If;
				main_poliz[i][j] = tmp;
				condition_stack.push(tmp);
			}
			else if (main_poliz[i][j] -> get_type() == ELSE) {
				if (condition_stack.empty() || condition_stack.top() -> get_type() != IF) {
					errorElseLogic(i);
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
				if (condition_stack.empty()) {
					errorFBracketCount(i);
				}
				if (condition_stack.top() -> get_type() == IF || condition_stack.top() -> get_type() == ELSE || condition_stack.top() -> get_type() == WHILE) {
					if (condition_stack.top() -> get_pos_start().first == -1) {
						condition_stack.top() -> set_pos_start(std::pair<int, int>(i, j));
					}
					else {
						errorFBracketCount(i);
					}
				}
			}
			else if (main_poliz[i][j] -> get_type() == FRBRACKET) {
				if (condition_stack.empty()) {
					errorFBracketCount(i);
				}
				if (condition_stack.top() -> get_type() == IF || condition_stack.top() -> get_type() == ELSE || condition_stack.top() -> get_type() == WHILE) {
					if (condition_stack.top() -> get_pos_start().first == -1) {
						errorFBracketCount(i);
					}
					if (condition_stack.top() -> get_pos_end().first == -1) {
						condition_stack.top() -> set_pos_end(std::pair<int, int>(i, j));
					}
					else {
						errorFBracketCount(i);
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
							errorFBracketCount(i);
						}
						else {
							condition_stack.top() -> set_else_ptr(tmp);
							condition_stack.pop();
						}
					}
				}
			}
		}
	}
	while (!condition_stack.empty()) {
		if (condition_stack.top() -> get_type() != IF || condition_stack.top() -> get_pos_start().first == -1 || condition_stack.top() -> get_pos_end().first == -1) {
			errorConditionLogic();
		}
		condition_stack.pop();
	}
}

void Algorithm::defineFunctions() {
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			if (main_poliz[i][j] -> get_type() == FUNCTION && main_poliz[i][j] -> is_definition()) {
				if (table_function.find(main_poliz[i][j] -> get_name()) != table_function.end()) {
					errorSimillarFunctions(i, j);
				}
				Function *new_function = new Function(main_poliz[i][j] -> get_name(), main_poliz[i][j] -> get_arguments(),
								      main_poliz[i][j] -> is_definition());
				new_function -> set_define_position(std::pair<int, int>(i, j));
				table_function.insert(std::pair<std::string, Function *>(new_function -> get_name(), new_function));
			}
		}
	}
}

void Algorithm::printLine() {
	std::cout << "------------------------------------" << std::endl;
}

void Algorithm::printPolizTable() {
	printLine();
	std::cout << "poliz:" << std::endl;
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			main_poliz[i][j] -> print();
		}
		std::cout << std::endl;
	}
}

void Algorithm::printVariableTable() {
	printLine();
	std::cout << "variable:" << std::endl;
	for (std::map<std::string, Variable *>::const_iterator i = stack_function.top() -> _table_variable.begin(); i != stack_function.top() -> _table_variable.end(); ++i) {
		std::cout << i -> first << '=' << i -> second -> get_value() << std::endl;
	}
}

void Algorithm::printArrayTable() {
	printLine();
	std::cout << "array:" << std::endl;
	for (std::map<std::string, Array *>::const_iterator i = stack_function.top() -> _table_array.begin(); i != stack_function.top() -> _table_array.end(); ++i) {
		i -> second -> print_elements();
		std::cout << std::endl;
	}
}

void Algorithm::printLabelTable() {
	printLine();
	std::cout << "label:" << std::endl;
	for (std::map<std::string, Label *>::const_iterator i = table_label.begin(); i != table_label.end(); ++i) {
		std::cout << i -> first << std::endl;
	}
}

void Algorithm::printFunctionTable() {
	printLine();
	std::cout << "function:" <<std::endl;
	for (std::map<std::string, Function *>::const_iterator i = table_function.begin(); i != table_function.end(); ++i) {
		i -> second -> print();
		for (std::map<std::string, Variable *>::const_iterator j = i -> second -> _table_variable.begin(); j != i -> second -> _table_variable.end(); ++j) {
			j -> second -> print();
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Algorithm::deleteData() {
	for (auto i: stack_function.top() -> _table_variable) {
		delete i.second;
	}
	for (auto i: stack_function.top() -> _table_array) {
		delete i.second;
	}
	for (auto i: table_label) {
		delete i.second;
	}
	for (auto i: table_function) {
		delete i.second;
	}
	for (int i = 0; i < main_poliz.size(); ++i) {
		for (int j = 0; j < main_poliz[i].size(); ++j) {
			delete main_poliz[i][j];
		}
	}
	delete stack_function.top();
	stack_function.pop();
}
