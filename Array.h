#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include "Lexem.h"

class Array: public Lexem {
	static OBJECT _type;
	std::string _name;
	std::vector<int> _data;
	int _size, _index;
public:
	Array();
	Array(std::string name);
	Array(std::string name, std::vector<int> data);
	virtual OBJECT get_type() const;
	virtual int get_priority() const;
	virtual std::string get_name() const;
	virtual int get_value() const;
	virtual std::vector<int> get_data() const;
	int get_table_value(int index);
	int get_size() const;
	int get_index() const;
	virtual void set_value(int value);
	void set_table_value(int value, int index);
	void set_index(int index);
	virtual void stack_evaluate(std::stack<Lexem *> &stack) const;
	virtual void print() const;
	void print_elements() const;
};

extern std::map<std::string, Array *> table_array;

#endif
