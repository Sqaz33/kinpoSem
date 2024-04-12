#include "Action.h"

Action::Action(Operation oper, const BigRealNumber* term1, const BigRealNumber* term2) {
	this->oper = oper;
	this->term1 = *term1;
	this->term2 = *term2;
	termCount = term2 == nullptr ? 1 : 0;
	if (!checkArity()) {
		throw runtime_error("Ошибка создания объекта: указано неверное количество операндов для операции " 
							+ stdStringFromOper(this->oper) + ".");
	}
}

Action Action::fromStdStrings(const string& oper, const string& term1, const string& term2) {
	bool isError = false;
	stringstream error;
	BigRealNumber t1{};
	BigRealNumber t2{};
	try { 
		t1 = BigRealNumber::fromStdString(term1);
	} catch (const runtime_error& e) {
		isError = true;
		error << e.what();
		error << " для операнда 1.\n";
		cout << error.str() << "\n";
	}
	try {
		t2 = BigRealNumber::fromStdString(term2);
	} catch (const runtime_error& e) {
		isError = true;
		error << e.what();
		error << " для операнда 2.\n";
		cout << error.str() << "\n";
	}

	Operation op = operFromStdString(oper);
	if (op == NO_OPER) {
		error << "Ошибка создания объекта: указана недоступная операция.\n";
		throw runtime_error(error.str());
	}
	try {
		Action act = Action(op, &t1, &t2);
		if (isError) {
			throw runtime_error(error.str());
		}
		return act;
	} catch (const runtime_error& e) {
		error << e.what();
		throw runtime_error(error.str());
	}
}

string Action::toStdString() {
	string str = term1.toStdString()
				+ " "
				+ term2.toStdString()
				+ " "
				+ stdStringFromOper(oper)
				+ "\n";
	return str;
}

BigRealNumber Action::perform() {
	BigRealNumber rs{};
	switch (oper) {
		case ADD:
			rs = term1 + term2;
			break;
		case SUBT:
			rs = term1 - term2;
			break;
		case MUL:
			rs = term1 * term2;
			break;
		case DIV:
			rs = term1 / term2;
			break;
		case POW:
			rs = term1.pow(term2);
			break;
		case FACT:
			rs = term1.factorial();
			break;
		case EQUALS:
			rs = term1 == term2;
			break;
		case NOT_EQUALS:
			rs = term1 != term2;
			break;
		case LESS:
			rs = term1 < term2;
			break;
		case NO_MORE:
			rs = term1 <= term2;
			break;
		case MORE:
			rs = term1 > term2;
			break;
		case NO_LESS:
			rs = term1 >= term2;
			break;
	}
	return rs;
}

bool Action::checkArity() {
	if (oper == FACT && termCount > 1) {
		return false;
	}
	return termCount == 2;
}

Operation operFromStdString(const string& oper) {
	unordered_map<string, Operation> stringToOper{
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
	return stringToOper.count(oper) ? stringToOper[oper] : NO_OPER;
}

string stdStringFromOper(Operation oper) {
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
		{NO_LESS, "no_less"},
		{NO_OPER, "no_oper"}
	};
	return operToString[oper];
}