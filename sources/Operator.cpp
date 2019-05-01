#include <iostream>
#include <stack>
#include <string>
#include <map>
#include <tuple>
#include "../headers/Variable.h"
#include "../headers/Operator.h"
#include "../headers/Number.h"
#include "../headers/Label.h"
#include "../headers/Array.h"
#include "../headers/Function.h"
#include "../headers/Algorithm.h"

OBJECT Assign::_type = ASSIGN;
OBJECT Plus::_type = PLUS;
OBJECT Minus::_type = MINUS;
OBJECT Multiply::_type = MULTIPLY;
OBJECT Mod::_type = MOD;
OBJECT Division::_type = DIVISION;
OBJECT LBracket::_type = LBRACKET;
OBJECT RBracket::_type = RBRACKET;
OBJECT Bit_And::_type = BITAND;
OBJECT Bit_Or::_type = BITOR;
OBJECT Bit_Xor::_type = BITXOR;
OBJECT Bit_Shift_Left::_type = BLS;
OBJECT Bit_Shift_Right::_type = BRS;
OBJECT Equally::_type = EQ;
OBJECT Not_Equally::_type = NEQ;
OBJECT Less::_type = LT;
OBJECT Greater::_type = GT;
OBJECT Less_or_Equally::_type = LEQ;
OBJECT Greater_or_Equally::_type = GEQ;
OBJECT Goto::_type = GOTO;
OBJECT If::_type = IF;
OBJECT Else::_type = ELSE;
OBJECT While::_type = WHILE;
OBJECT FLBracket::_type = FLBRACKET;
OBJECT FRBracket::_type = FRBRACKET;
OBJECT RLBracket::_type = RLBRACKET;
OBJECT RRBracket::_type = RRBRACKET;
OBJECT Print::_type = PRINT;
OBJECT New_Line::_type = NEWLINE;
OBJECT Return::_type = RETURN;
OBJECT Comma::_type = COMMA;
OBJECT EndFunction::_type = ENDFUNCTION;

extern int cur_row, cur_col;
extern std::map<std::string, Label *> table_label;
extern std::map<std::string, Array *> table_array;
extern std::stack<Function *> stack_function;

int Operator::get_value() const {
	return 0;
}

std::string Operator::get_name() const {
	return "";
}

Assign::Assign() {}

OBJECT Assign::get_type() const {
	return _type;
}

int Assign::get_priority() const {
	return PRIORITY[get_type()];
}

void Assign::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {	
		errorOperation('=');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {	
		errorOperation('=');
	}
	Lexem *a = stack.top();
	stack.pop();
	if (a -> get_type() != VARIABLE && a -> get_type() != ARRAY) {
		errorOperation('=');
	}
	if (a -> get_type() == VARIABLE) {
		if (stack_function.top() -> _table_variable.find(a -> get_name()) != stack_function.top() -> _table_variable.end()) {
			stack_function.top() -> _table_variable[a -> get_name()] -> set_value(b -> get_value());
		}
		else {
			stack_function.top() -> _table_variable.insert(std::pair<std::string, Variable *>(a -> get_name(), new Variable(a -> get_name(), b -> get_value())));
		}
	}
	else {
		if (stack_function.top() -> _table_array.find(a -> get_name()) != stack_function.top() -> _table_array.end()) {
			a -> set_value(b -> get_value());
		}
		else {
			stack_function.top() -> _table_array.insert(std::pair<std::string, Array *>(a -> get_name(), new Array(a -> get_name())));
			a -> set_value(b -> get_value());
		}
	}
	stack.push(b);
	delete a;
}

void Assign::print() const {
	std::cout << '=';
}

Plus::Plus() {}

OBJECT Plus::get_type() const {
	return _type;
}

int Plus::get_priority() const {
	return PRIORITY[get_type()];
}

void Plus::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('+');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('+');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() + b -> get_value()));
	delete a;
	delete b;
}

void Plus::print() const {
	std::cout << '+';
}

Minus::Minus() {}

OBJECT Minus::get_type() const {
	return _type;
}

int Minus::get_priority() const {
	return PRIORITY[get_type()];
}

void Minus::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('-');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('-');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() - b -> get_value()));
	delete a;
	delete b;
}

void Minus::print() const {
	std::cout << '-';
}

Multiply::Multiply() {}

OBJECT Multiply::get_type() const {
	return _type;
}

int Multiply::get_priority() const {
	return PRIORITY[get_type()];
}

void Multiply::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('*');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('*');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() * b -> get_value()));
	delete a;
	delete b;
	//std::cout << a.get_value() << '*' << b.get_value() << std::endl;
}

void Multiply::print() const {
	std::cout << '*';
}

Mod::Mod() {}

OBJECT Mod::get_type() const {
	return _type;
}

int Mod::get_priority() const {
	return PRIORITY[get_type()];
}

void Mod::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('%');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('%');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() % b -> get_value()));
	delete a;
	delete b;
	//std::cout << a.get_value() << '*' << b.get_value() << std::endl;
}

void Mod::print() const {
	std::cout << '%';
}

Division::Division() {}

OBJECT Division::get_type() const {
	return _type;
}

int Division::get_priority() const {
	return PRIORITY[get_type()];
}

void Division::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('/');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('/');
	}
	Lexem *a = stack.top();
	stack.pop();
	if (b -> get_value() == 0) {
		errorOperation('/');
	}
	stack.push(new Number(a -> get_value() / b -> get_value()));
	delete a;
	delete b;
	//std::cout << a.get_value() << '/' << b.get_value() << std::endl;
}

void Division::print() const {
	std::cout << '/';
}

LBracket::LBracket() {}

OBJECT LBracket::get_type() const {
	return _type;
}

int LBracket::get_priority() const {
	return PRIORITY[get_type()];
}

void LBracket::stack_evaluate(std::stack<Lexem *> &stack) const {}

void LBracket::print() const {
	std::cout << '(';
}

RBracket::RBracket() {}

OBJECT RBracket::get_type() const {
	return _type;
}

int RBracket::get_priority() const {
	return PRIORITY[get_type()];
}

void RBracket::stack_evaluate(std::stack<Lexem *> &stack) const {}

void RBracket::print() const {
	std::cout << ')';
}

Bit_And::Bit_And() {}

OBJECT Bit_And::get_type() const {
	return _type;
}

int Bit_And::get_priority() const {
	return PRIORITY[get_type()];
}

void Bit_And::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('&');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('&');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) & (b -> get_value())));
	delete a;
	delete b;

}

void Bit_And::print() const {
	std::cout << "&";
}

Bit_Or::Bit_Or() {}

OBJECT Bit_Or::get_type() const {
	return _type;
}

int Bit_Or::get_priority() const {
	return PRIORITY[get_type()];
}

void Bit_Or::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('|');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('|');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() | b -> get_value()));
	delete a;
	delete b;

}

void Bit_Or::print() const {
	std::cout << "|";
}

Bit_Xor::Bit_Xor() {}

OBJECT Bit_Xor::get_type() const {
	return _type;
}

int Bit_Xor::get_priority() const {
	return PRIORITY[get_type()];
}

void Bit_Xor::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('^');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('^');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() ^ b -> get_value()));
	delete a;
	delete b;

}

void Bit_Xor::print() const {
	std::cout << "^";
}

Bit_Shift_Right::Bit_Shift_Right() {}

OBJECT Bit_Shift_Right::get_type() const {
	return _type;
}

int Bit_Shift_Right::get_priority() const {
	return PRIORITY[get_type()];
}

void Bit_Shift_Right::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('>', '>');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('>', '>');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() >> b -> get_value()));
	delete a;
	delete b;

}

void Bit_Shift_Right::print() const {
	std::cout << ">>";
}

Bit_Shift_Left::Bit_Shift_Left() {}

OBJECT Bit_Shift_Left::get_type() const {
	return _type;
}

int Bit_Shift_Left::get_priority() const {
	return PRIORITY[get_type()];
}

void Bit_Shift_Left::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('<', '<');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('<', '<');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number(a -> get_value() << b -> get_value()));
	delete a;
	delete b;

}

void Bit_Shift_Left::print() const {
	std::cout << "<<";
}

Equally::Equally() {}

OBJECT Equally::get_type() const {
	return _type;
}

int Equally::get_priority() const {
	return PRIORITY[get_type()];
}

void Equally::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('=', '=');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('=', '=');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) == (b -> get_value())));
	delete a;
	delete b;

}

void Equally::print() const {
	std::cout << "==";
}


Not_Equally::Not_Equally() {}

OBJECT Not_Equally::get_type() const {
	return _type;
}

int Not_Equally::get_priority() const {
	return PRIORITY[get_type()];
}

void Not_Equally::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('!', '=');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('!', '=');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) != (b -> get_value())));
	delete a;
	delete b;

}

void Not_Equally::print() const {
	std::cout << "!=";
}

Less::Less() {}

OBJECT Less::get_type() const {
	return _type;
}

int Less::get_priority() const {
	return PRIORITY[get_type()];
}

void Less::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('<');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('<');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) < (b -> get_value())));
	delete a;
	delete b;

}

void Less::print() const {
	std::cout << "<";
}

Greater::Greater() {}

OBJECT Greater::get_type() const {
	return _type;
}

int Greater::get_priority() const {
	return PRIORITY[get_type()];
}

void Greater::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('>');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('>');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) > (b -> get_value())));
	delete a;
	delete b;

}

void Greater::print() const {
	std::cout << ">";
}

Less_or_Equally::Less_or_Equally() {}

OBJECT Less_or_Equally::get_type() const {
	return _type;
}

int Less_or_Equally::get_priority() const {
	return PRIORITY[get_type()];
}

void Less_or_Equally::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('<', '=');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('<', '=');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) <= (b -> get_value())));
	delete a;
	delete b;

}

void Less_or_Equally::print() const {
	std::cout << "<=";
}

Greater_or_Equally::Greater_or_Equally() {}

OBJECT Greater_or_Equally::get_type() const {
	return _type;
}

int Greater_or_Equally::get_priority() const {
	return PRIORITY[get_type()];
}

void Greater_or_Equally::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('>', '=');
	}
	Lexem *b = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('>', '=');
	}
	Lexem *a = stack.top();
	stack.pop();
	stack.push(new Number((a -> get_value()) >= (b -> get_value())));
	delete a;
	delete b;

}

void Greater_or_Equally::print() const {
	std::cout << ">=";
}

Goto::Goto() {}

Goto::Goto(std::string name) {
	_name = name;
}

OBJECT Goto::get_type() const {
	return _type;
}


int Goto::get_priority() const {
	return PRIORITY[_type];
}

std::string Goto::get_name() const {
	return _name;
}

void Goto::stack_evaluate(std::stack<Lexem *> &stack) const {
	cur_row = table_label[get_name()] -> get_row();
	cur_col = table_label[get_name()] -> get_col() + 1;
}

void Goto::print() const {
	std::cout << "goto " << _name;
}

int Condition::get_value() const {
	return 0;
}

std::string Condition::get_name() const {
	return "";
}

std::pair<int, int> Condition::get_pos_start() const {
	return std::pair<int, int>(0, 0);
}

std::pair<int, int> Condition::get_pos_end() const {
	return std::pair<int, int>(0, 0);
}

Condition *Condition::get_else_ptr() const {
	return nullptr;
}

void Condition::set_pos_start(std::pair<int, int> pair) {}

void Condition::set_pos_end(std::pair<int, int> pair) {}

void Condition::set_else_ptr(Condition *ptr) {}

If::If() {
	_pos_start = std::pair<int, int>(-1, -1);
	_pos_end = std::pair<int, int>(-1, -1);
	_else_ptr = nullptr;
}

OBJECT If::get_type() const {
	return _type;
}

int If::get_priority() const {
	return PRIORITY[_type];
}

void If::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('i', 'f');
	}
	Lexem *a = stack.top();
	stack.pop();
	if (a -> get_value() == 0) {
		if (_else_ptr != nullptr) {
			cur_row = _else_ptr -> get_pos_start().first;
			cur_col = _else_ptr -> get_pos_start().second;
		}
		else {
			cur_row = _pos_end.first;
			cur_col = _pos_end.second;
		}
	}
	else {
		cur_row = _pos_start.first;
		cur_col = _pos_start.second;
	}
	delete a;
}

void If::print() const {
	std::cout << "if";
}

std::pair<int, int> If::get_pos_start() const {
	return _pos_start;
}

std::pair<int, int> If::get_pos_end() const {
	return _pos_end;
}

Condition *If::get_else_ptr() const {
	return _else_ptr;
}

void If::set_pos_start(std::pair<int, int> pair) {
	_pos_start = pair;
}

void If::set_pos_end(std::pair<int, int> pair) {
	_pos_end = pair;
}

void If::set_else_ptr(Condition *ptr) {
	_else_ptr = ptr;
}

Else::Else() {
	_pos_start = std::pair<int, int>(-1, -1);
	_pos_end = std::pair<int, int>(-1, -1);
}

OBJECT Else::get_type() const {
	return _type;
}

int Else::get_priority() const {
	return PRIORITY[_type];
}

void Else::stack_evaluate(std::stack<Lexem *> &stack) const {
	cur_row = _pos_end.first;
	cur_col = _pos_end.second;
}

void Else::print() const {
	std::cout << "else";
}

std::pair<int, int> Else::get_pos_start() const {
	return _pos_start;
}

std::pair<int, int> Else::get_pos_end() const {
	return _pos_end;
}

void Else::set_pos_start(std::pair<int, int> pair) {
	_pos_start = pair;
}

void Else::set_pos_end(std::pair<int, int> pair) {
	_pos_end = pair;
}

While::While() {
	_pos_start = std::pair<int, int>(-1, -1);
	_pos_end = std::pair<int, int>(-1, -1);
}

While::While(int label_number) {
	_pos_start = std::pair<int, int>(-1, -1);
	_pos_end = std::pair<int, int>(-1, -1);
	_label_number = label_number;
}

OBJECT While::get_type() const {
	return _type;
}

int While::get_priority() const {
	return PRIORITY[_type];
}

void While::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('w', 'l');
	}
	Lexem *a = stack.top();
	stack.pop();
	if (a -> get_value() == 0) {
		cur_row = _pos_end.first;
		cur_col = _pos_end.second + 1;
		
	}
	else {
		cur_row = _pos_start.first;
		cur_col = _pos_start.second;
	}
	delete a;
}

void While::print() const {
	std::cout << "while ";
}

std::pair<int, int> While::get_pos_start() const {
	return _pos_start;
}

std::pair<int, int> While::get_pos_end() const {
	return _pos_end;
}

int While::get_value() const {
	return _label_number;
}

void While::set_pos_start(std::pair<int, int> pair) {
	_pos_start = pair;
}

void While::set_pos_end(std::pair<int, int> pair) {
	_pos_end = pair;
}

FLBracket::FLBracket() {}

OBJECT FLBracket::get_type() const {
	return _type;
}

int FLBracket::get_priority() const {
	return PRIORITY[_type];
}

void FLBracket::stack_evaluate(std::stack<Lexem *> &stack) const {
}

void FLBracket::print() const {
	std::cout << "{";
}

FRBracket::FRBracket() {}

OBJECT FRBracket::get_type() const {
	return _type;
}

int FRBracket::get_priority() const {
	return PRIORITY[_type];
}

void FRBracket::stack_evaluate(std::stack<Lexem *> &stack) const {}

void FRBracket::print() const {
	std::cout << "}";
}

std::pair<int, int> FRBracket::get_jump_pos() const {
	return _jump_pos;
}

void FRBracket::set_jump_pos(std::pair<int, int> pair) {
	_jump_pos = pair;
}

RLBracket::RLBracket() {}

OBJECT RLBracket::get_type() const {
	return _type;
}

int RLBracket::get_priority() const {
	return PRIORITY[_type];
}

void RLBracket::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('[');
	}
	Lexem *fir = stack.top();
	stack.pop();
	if (stack.empty()) {
		errorOperation('[');
	}
	Lexem *arr = stack.top();
	if (stack_function.top() -> _table_array.find(arr -> get_name()) == stack_function.top() -> _table_array.end()) {
			stack_function.top() -> _table_array.insert(std::pair<std::string, Array *>(arr -> get_name(), new Array(arr -> get_name())));
	}
	arr -> set_index(fir -> get_value());
	delete fir;

}

void RLBracket::print() const {
	std::cout << "[";
}

RRBracket::RRBracket() {}

OBJECT RRBracket::get_type() const {
	return _type;
}

int RRBracket::get_priority() const {
	return PRIORITY[_type];
}

void RRBracket::stack_evaluate(std::stack<Lexem *> &stack) const {}

void RRBracket::print() const {
	std::cout << "]";
}

Print::Print() {}

OBJECT Print::get_type() const {
	return _type;
}

int Print::get_priority() const {
	return PRIORITY[_type];
}

void Print::stack_evaluate(std::stack<Lexem *> &stack) const {
	if (stack.empty()) {
		errorOperation('p', 'r');
	}
	Lexem *a = stack.top();
	std::cout << a -> get_value() << ' ';
}

void Print::print() const {
	std::cout << "print ";
}

New_Line::New_Line() {}

OBJECT New_Line::get_type() const {
	return _type;
}

int New_Line::get_priority() const {
	return PRIORITY[_type];
}

void New_Line::stack_evaluate(std::stack<Lexem *> &stack) const {
	std::cout << std::endl;
}

void New_Line::print() const {
	std::cout << "newline ";
}

Return::Return() {}

OBJECT Return::get_type() const {
	return _type;
}

int Return::get_priority() const {
	return PRIORITY[_type];
}

void Return::stack_evaluate(std::stack<Lexem *> &stack) const {
	cur_row = stack_function.top() -> get_start_position().first;
	cur_col = stack_function.top() -> get_start_position().second;
	for (auto i: stack_function.top() -> _table_variable) {
		delete i.second;
	}
	for (auto i: stack_function.top() -> _table_array) {
		delete i.second;
	}
	if (!stack.empty()) {
		Lexem *tmp = stack.top();
		Number *number = new Number(tmp -> get_value());
		delete stack_function.top();
		stack_function.pop();
		stack_function.top() -> _stack.push(number);
	}
	else {	
		stack_function.pop();
	}
}

void Return::print() const {
	std::cout << "return ";
}

Comma::Comma() {}

OBJECT Comma::get_type() const {
	return _type;
}

int Comma::get_priority() const {
	return PRIORITY[_type];
}

void Comma::stack_evaluate(std::stack<Lexem *> &stack) const {}

void Comma::print() const {
	std::cout << ',';
}

EndFunction::EndFunction() {}

OBJECT EndFunction::get_type() const {
	return _type;
}

int EndFunction::get_priority() const {
	return PRIORITY[_type];
}

void EndFunction::stack_evaluate(std::stack<Lexem *> &stack) const {
	cur_row = stack_function.top() -> get_start_position().first;
	cur_col = stack_function.top() -> get_start_position().second;
	stack_function.pop();
}

void EndFunction::print() const {
	std::cout << "endef";
}
