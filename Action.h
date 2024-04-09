#pragma once

#include <unordered_map>
#include "string"

#include "QString"
#include "qregexp"

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

struct Result {
	string term1;
	string term2;
	string operation;
	string result;
	bool isError;
};

// Установить ошибку в результате
void setErrorToResult(const string& errorCode, Result& res);

class Action {
private:
	BigRealNumber term1;
	BigRealNumber term2;
	Operation oper;
	Result res;

	void setTerm(const string &term, int number);
	void setOperation(const string &oper);
	void checkAction();

	unordered_map<string, Operation> stringToOper {
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


	unordered_map<Operation, string> operToString{
		{ADD, "add"},
		{SUBT, "subt"},
		{MUL, "mul"},
		{DIV, "div"},
		{POW, "pow"},
		{FACT, "fact"},
		{EQUALS, "equals"},
		{NOT_EQUALS, "not_equals"},
		{LESS, "less"},
		{NO_MORE, "no_more"},
		{MORE, "more"},
		{NO_LESS, "no_less"}
	};

public:
	Action(const string& term1, const string& term2, const string& oper);
	Result perform();
};

