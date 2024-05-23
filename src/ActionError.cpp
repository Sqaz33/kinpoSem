#include "../include/ActionError.h"

std::string ActionError::toStdString() const{
	return errorTypeToStdString(e);
}

std::string ActionBuildError::toStdString() const {
	return "Error building action on line "
			+ std::to_string(xmlLineNumber)
			+ "xml-file: "
			+ ActionError::toStdString();
}
void ActionBuildError::setXmlLineNumber(int ln) {
	xmlLineNumber = ln;
}

std::string ActionPerformError::toStdString() const {
	return "Error performing an action on a line "
			+ std::to_string(actionNumber)
			+ "xml-file: "
			+ ActionError::toStdString();
}
void ActionPerformError::setActionNumber(int a) {
	actionNumber = a;
}

std::string errorTypeToStdString(ActionErrorType e) {
	std::unordered_map<ActionErrorType, std::string> errorTypeToString {
		{NO_OPER_E, "No operands in expression"},
		{INVALID_ARITY, "Invalid number of arguments"},
		{INVALID_OPERAND_FORMAT, "Format error for one of the operands"},
		{INVALID_LENGTH, "The length or size of one of the lines exceeds 1000 characters"},
		{DIVISION_BY_ZERO, "Division by zero"},
		{OPERAND_WITH_FRACTIONAL_PART_POW_FACT, "The operand cannot be fractional for pow or fact operations"},
		{OPERAND_LESS_ZERO_POW_FACT, "Operand cannot be less than zero for pow or fact operations"}
	};
	return errorTypeToString[e];
}
