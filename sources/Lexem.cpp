#include <iostream>
#include <vector>
#include <string>
#include "../headers/Lexem.h"

int PRIORITY[] = {
	-100,
	-50, -50, -49, -50,
	-5,
	-2, -2,
	0, 0, -45, -45,
	1,
	2,
	3,
	4,
	5,
	6,
	7, 7,
	8, 8, 8, 8,
	9, 9,
	10, 10,
	11, 11, 11,
	-10, -10, -10,
	100, 100, 100, 100,
	-200, 200, -200
};

Lexem::Lexem() {}

int Lexem::get_index() const{
	return 0;
}

int Lexem::get_size() const {
	return 0;
}

int Lexem::get_argument_count() const {
	return 0;
}

void Lexem::set_value(int value) {}

void Lexem::set_index(int index) {}

std::vector<int> Lexem::get_data() const {
	return std::vector<int>();
}

std::vector<std::string> Lexem::get_arguments() const {
	return std::vector<std::string>();
}

bool Lexem::is_definition() const {
	return false;
}
