#pragma once
#include "BigRealNumber.h"
#include "string"
#include "QString"
#include "qregexp"
#include "qhash"

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

struct Result {
	string term1;
	string term2;
	string operation;
	string result;
	bool isError;
};

class Action {
private:
	BigRealNumber term1;
	BigRealNumber term2;
	Operation oper;
	Result res;
	// далее будут проверки term1,2 и oper
	void setTerm(const string &term, int number);
	void setOperation(const string &oper);
	void checkAction();

	QHash<string, Operation> toOper{
		{"add", ADD},
		{"subt", SUBT},
		{"mul", MUL},
		{"div", DIV},
		{"pow", POW},
		{"fact", FACT},
		{"equals", EQUALS},
		{"not_equals", NOT_EQUALS},
		{"less", LESS},
		{"no_more", NO_MORE},
		{"more", MORE},
		{"no_less",  NO_LESS}
	};


public:
	Action(const string& term1, const string& term2, const string& oper);
	// если в res уже isError вернуть res
	Result perform();
};

void setErrorToResult(const string& errorCode, Result &res);