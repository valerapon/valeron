install:
	clear && g++ -o main -std=c++17 main.cpp sources/Algorithm.cpp sources/Lexem.cpp sources/Number.cpp sources/Operator.cpp sources/Variable.cpp sources/Label.cpp sources/Array.cpp sources/Function.cpp sources/Error.cpp
