#ifndef ERROR_H
#define ERROR_H

void error();

void errorInput(int col);

void errorNoGotoTarget(int col);

void errorNoDefTarget(int col);

void errorFunctionName(int col);

void errorFunctionArgument(int col);

void errorNumberBuild(int col);

void errorWordFirstSymbol(int col);

void errorSimillarLabels(int row, int col);

void errorElseLogic(int row);

void errorFBracketCount(int row);

void errorConditionLogic();

void errorSimillarFunctions(int row, int col);

void errorTypeCompatibility(int col);

void errorOperation(char op1, char op2 = '\0');

void errorFunctionNotFound();

void errorFewArguments();

void errorEqualFunctionArguments();

#endif
