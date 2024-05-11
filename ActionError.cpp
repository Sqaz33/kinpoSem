#include "ActionError.h"

std::string ActionError::toStdString() const{
	return errorTypeToStdSting(e);
}

std::string ActionBuildError::toStdString() const {
	return "Ошибка создания объекта в строке "
			+ std::to_string(xmlLineNumber)
			+ "xml-файла: "
			+ ActionError::toStdString();
}
void ActionBuildError::setXmlLineNumber(int ln) {
	xmlLineNumber = ln;
}

std::string ActionPerformError::toStdString() const {
	return "Вычисления для действия №"
			+ std::to_string(actionNumber)
			+ "xml-файла: "
			+ ActionError::toStdString();
}
void ActionPerformError::setActionNumber(int a) {
	actionNumber = a;
}

std::string errorTypeToStdSting(ActionErrorType e) {
	std::unordered_map<ActionErrorType, std::string> errorTypeToString {
	{NO_OPER_E, "указана недоступная операция"},
	{INVALID_ARITY, "недопустимое количество операндов"},
	{INVALID_OPERAND_FORMAT, "указан неверный формат операнда"},
	{INVALID_LENGTH, "дробная или целая часть числа содерит более 1000 цифр"},
	{DIVISION_BY_ZERO, "деление на ноль"},
	{OPERAND_WITH_FRACTIONAL_PART_POW_FACT, "операнд имеет дробную часть для операции pow или fact"},
	{OPERAND_LESS_ZERO_POW_FACT, "операнд меньше нуля для операции pow или fact"}
	};
	return errorTypeToString[e];
}
