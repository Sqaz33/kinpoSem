#pragma once
#include "unordered_map"
#include "string"

enum ActionErrorName {
	NO_OPER_E, // Ошибка создания объекта
	INVALID_ARITY, // Ошибка создания объекта
	INVALID_OPERAND_FORMAT, // Ошибка создания объекта
	INVALID_LENGTH, // Ошибка создания объекта или вычисления
	DIVISION_BY_ZERO, // Ошибка вычисления
	OPERAND_WITH_FRACTIONAL_PART_POW_FACT, // Ошибка вычисления
	OPERAND_LESS_ZERO_POW_FACT // Ошибка вычисления 
};
std::string eNameToStdSting(ActionErrorName e);


class ActionError {
private:
	ActionErrorName e;
public:
	ActionError(ActionErrorName e) : e(e) {};
	virtual std::string toStdString() const;
};

class ActionBuildError : ActionError {
private:
	int xmlLineNumber;
public:
	ActionBuildError(ActionErrorName e) : ActionError(e), xmlLineNumber(-1) {};
	void setXmlLineNumber(int ln);
	std::string toStdString() const override;
};

class ActionPerformError : ActionError {
private:
	int actionNumber;
public:
	ActionPerformError(ActionErrorName e) : ActionError(e), actionNumber(-1) {};
	std::string toStdString() const override;
	void setActionNumber(int a);
};

