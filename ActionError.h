#pragma once
#include "unordered_map"
#include "string"

enum ActionErrorName {
	NO_OPER_E, // ������ �������� �������
	INVALID_ARITY, // ������ �������� �������
	INVALID_OPERAND_FORMAT, // ������ �������� �������
	INVALID_LENGTH, // ������ �������� ������� ��� ����������
	DIVISION_BY_ZERO, // ������ ����������
	OPERAND_WITH_FRACTIONAL_PART_POW_FACT, // ������ ����������
	OPERAND_LESS_ZERO_POW_FACT // ������ ���������� 
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

