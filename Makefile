install:
	clear && mkdir -p bin && g++ -o bin/main main.cpp sources/Algorithm.cpp sources/Lexem.cpp sources/Number.cpp sources/Operator.cpp sources/Variable.cpp sources/Label.cpp sources/Array.cpp sources/Function.cpp sources/Error.cpp
