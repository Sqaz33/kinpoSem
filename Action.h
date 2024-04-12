#pragma once

#include <unordered_map>
#include "string"
#include "sstream"
#include "QString"

#include "BigRealNumber.h"

enum Operation {
	ADD,
	SUBT,
	MUL,
	DIV,
	POW,
	FACT,
	EQUALS,
	NOT_EQUALS,
	LESS,
	NO_MORE,
	MORE,
	NO_LESS,
	NO_OPER
};
Operation operFromStdString(const string& oper);
string stdStringFromOper(Operation oper);

class Action {
private:
	BigRealNumber term1;
	BigRealNumber term2;
	Operation oper;
	int termCount;

	bool checkArity();

public:
	static Action fromStdStrings(const string& oper, const string& term1, const string& term2);
	Action(Operation oper, const BigRealNumber* term1, const BigRealNumber* term2 = nullptr);
	BigRealNumber perform();
	string toStdString();
};

