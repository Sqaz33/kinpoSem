#include "Action.h"

Action::Action(const string& term1, const string& term2, const string& oper) {
	res = Result{};
	setTerm(term1, 1);
	setTerm(term2, 2);
	setOperation(oper);
}

Result Action::perform() {
	Result r{};
	if (res.isError) {
		r = res;
		return r;
	}

	try {
		BigRealNumber rs;
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
				rs = term1.pow()
		}
		r.term1 = term1.toString();
		r.term2 = term2.toString();
		r.operation = toOper.key(oper);
		r.result = rs.toString();

	} catch (const runtime_error& e) {
		setErrorToResult(e.what(), r);
	}
	return r;
}

void Action::setTerm(const string &term, int number) {
	if (res.isError) {
		return;
	}

	QRegExp rx("\-{0,1}\d+\.\d+");
	QString str = QString::fromStdString(term);

	bool isNegative = term.at(0) == '-';
	int point = (int)term.find('.');
	int intPrtLen = point - isNegative;
	int fractPrtLen = term.length() - intPrtLen - 1 - isNegative;

	if (rx.exactMatch(str) && intPrtLen <= 50 && fractPrtLen <= 50) {
		switch (number) {
			case 1:
				term1 = BigRealNumber(term);
				res.term1 = term;
				res.term2 = " ";
				break;
			case 2:
				term2 = BigRealNumber(term);
				res.term2 = term;
				break;
		}
	} else if (!rx.exactMatch(str)) {
		setErrorToResult("Ошибка чтения: неправильная запись операнда", res);
	} else if (intPrtLen > 50 || fractPrtLen > 50) {
		setErrorToResult(
			"Ошибка чтения: дробная или целая"
			"часть операнда содержит более 50 цифр",
			res
		);
	}
}

void Action::setOperation(const string &op) {
	if (res.isError) {
		return;
	}
	oper = toOper.value(op, NO_OPER);
	if (oper == NO_OPER) {
		setErrorToResult("Ошибка чтения: указана недоступная операция", res);
	}
}

void setErrorToResult(const string& errorCode, Result &res) {
	res.isError = true;
	res.term1 = "NaN";
	res.term2 = "NaN";
	res.operation = "NaN";
	res.result = errorCode;
}
