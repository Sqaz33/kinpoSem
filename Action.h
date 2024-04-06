#pragma once
#include "BigRealNumber.h"
#include "string"

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
	NO_LESS
};

struct Result {
	string term1;
	string term2;
	string result;
	bool isError;
	string errorCode;
};

class Action {
private:
	BigRealNumber term1;
	BigRealNumber term2;
	Operation oper;
	Result res;
	// далее будут проверки term1,2 и oper

public:
	Action(string& term1, string& term2, string& oper);
	// если в result уже isError вернуть, isError
	Result perform();
};

