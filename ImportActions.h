#pragma once
#include "string"
using namespace std;

enum operation {
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

struct action {
	int termCount;
	string term1;
	string term2;
	operation oper;
};

class ImportActions {

};

