#include "../include/ActionError.h"

std::string ActionError::toStdString() const{
	return errorTypeToStdString(e);
}

std::string ActionBuildError::toStdString() const {
	return "������ �������� ������� � ������ "
			+ std::to_string(xmlLineNumber)
			+ "xml-�����: "
			+ ActionError::toStdString();
}
void ActionBuildError::setXmlLineNumber(int ln) {
	xmlLineNumber = ln;
}

std::string ActionPerformError::toStdString() const {
	return "���������� ��� �������� �"
			+ std::to_string(actionNumber)
			+ "xml-�����: "
			+ ActionError::toStdString();
}
void ActionPerformError::setActionNumber(int a) {
	actionNumber = a;
}

std::string errorTypeToStdString(ActionErrorType e) {
	std::unordered_map<ActionErrorType, std::string> errorTypeToString {
	{NO_OPER_E, "������� ����������� ��������"},
	{INVALID_ARITY, "������������ ���������� ���������"},
	{INVALID_OPERAND_FORMAT, "������ �������� ������ ��������"},
	{INVALID_LENGTH, "������� ��� ����� ����� ����� ������� ����� 1000 ����"},
	{DIVISION_BY_ZERO, "������� �� ����"},
	{OPERAND_WITH_FRACTIONAL_PART_POW_FACT, "������� ����� ������� ����� ��� �������� pow ��� fact"},
	{OPERAND_LESS_ZERO_POW_FACT, "������� ������ ���� ��� �������� pow ��� fact"}
	};
	return errorTypeToString[e];
}
