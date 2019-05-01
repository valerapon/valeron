#ifndef OPERATOR_H
#define OPERATOR_H

#include <iostream>
#include <stack>
#include <string>
#include "Lexem.h"
#include "Variable.h"
#include "Number.h"
#include "Label.h"

class Operator: public Lexem {
public:
	virtual OBJECT get_type() const = 0;
	virtual int get_priority() const = 0;
	virtual int get_value() const;
	virtual std::string get_name() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const = 0;
	virtual void print() const = 0;
};

class Assign: public Operator {
	static OBJECT _type;
public:
	Assign();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;	
};

class Plus: public Operator {
	static OBJECT _type;
public:
	Plus();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Minus: public Operator {
	static OBJECT _type;
public:
	Minus();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Multiply: public Operator {
	static OBJECT _type;
public:
	Multiply();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Mod: public Operator {
	static OBJECT _type;
public:
	Mod();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Division: public Operator {
	static OBJECT _type;
public:
	Division();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class LBracket: public Operator {
	static OBJECT _type;
public:
	LBracket();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class RBracket: public Operator {
	static OBJECT _type;
public:
	RBracket();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Bit_And: public Operator {
	static OBJECT _type;
public:
	Bit_And();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Bit_Or: public Operator {
	static OBJECT _type;
public:
	Bit_Or();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Bit_Xor: public Operator {
	static OBJECT _type;
public:
	Bit_Xor();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Bit_Shift_Right: public Operator {
	static OBJECT _type;
public:
	Bit_Shift_Right();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Bit_Shift_Left: public Operator {
	static OBJECT _type;
public:
	Bit_Shift_Left();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Equally: public Operator {
	static OBJECT _type;
public:
	Equally();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Not_Equally: public Operator {
	static OBJECT _type;
public:
	Not_Equally();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Less: public Operator {
	static OBJECT _type;
public:
	Less();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Greater: public Operator {
	static OBJECT _type;
public:
	Greater();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Less_or_Equally: public Operator {
	static OBJECT _type;
public:
	Less_or_Equally();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Greater_or_Equally: public Operator {
	static OBJECT _type;
public:
	Greater_or_Equally();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Goto: public Operator {
	static OBJECT _type;
	std::string _name;
public:
	Goto();
	Goto(std::string name);
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual std::string get_name() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Condition: public Operator {
public:
	virtual OBJECT get_type() const = 0;
	virtual int get_priority() const = 0;
	virtual int get_value() const;
	virtual std::string get_name() const;
	virtual std::pair<int, int> get_pos_start() const;
	virtual std::pair<int, int> get_pos_end() const;
	virtual void set_pos_start(std::pair<int, int> pair);
	virtual void set_pos_end(std::pair<int, int> pair);
	virtual void set_else_ptr(Condition *ptr);
	virtual Condition *get_else_ptr() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const = 0;
	virtual void print() const = 0;

};

class If: public Condition {
	static OBJECT _type;
	std::pair<int, int> _pos_start, _pos_end;
	Condition *_else_ptr;
public:
	If();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
	virtual std::pair<int, int> get_pos_start() const;
	virtual std::pair<int, int> get_pos_end() const;
	virtual void set_pos_start(std::pair<int, int> pair);
	virtual void set_pos_end(std::pair<int, int> pair);
	virtual Condition *get_else_ptr() const;
	virtual void set_else_ptr(Condition *ptr);
};

class Else: public Condition {
	static OBJECT _type;
	std::pair<int, int> _pos_start, _pos_end;
public:
	Else();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
	std::pair<int, int> get_pos_start() const;
	std::pair<int, int> get_pos_end() const;
	void set_pos_start(std::pair<int, int> pair);
	void set_pos_end(std::pair<int, int> pair);
};

class While: public Condition {
	static OBJECT _type;
	std::pair<int, int> _pos_start, _pos_end;
	int _label_number;
public:	
	While();
	While(int label_number);
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
	virtual std::pair<int, int> get_pos_start() const;
	virtual std::pair<int, int> get_pos_end() const;
	virtual int get_value() const;
	virtual void set_pos_start(std::pair<int, int> pair);
	virtual void set_pos_end(std::pair<int, int> pair);
};

class FLBracket: public Condition {
	static OBJECT _type;
public:
	FLBracket();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class FRBracket: public Condition {
	static OBJECT _type;
	std::pair<int, int> _jump_pos;
public:
	FRBracket();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
	std::pair<int, int> get_jump_pos() const;
	void set_jump_pos(std::pair<int, int> pair);
};

class RLBracket: public Operator {
	static OBJECT _type;
public:
	RLBracket();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class RRBracket: public Operator {
	static OBJECT _type;
public:
	RRBracket();
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Print: public Operator {
	static OBJECT _type;
public:
	Print();
	virtual OBJECT get_type() const;;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class New_Line: public Operator {
	static OBJECT _type;
public:
	New_Line();
	virtual OBJECT get_type() const;;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Return: public Operator {
	static OBJECT _type;
public:
	Return();
	virtual OBJECT get_type() const;;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class Comma: public Operator {
	static OBJECT _type;
public:
	Comma();
	virtual OBJECT get_type() const;;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

class EndFunction: public Operator {
	static OBJECT _type;
public:
	EndFunction();
	virtual OBJECT get_type() const;;
	virtual int get_priority() const;
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
};

#endif
