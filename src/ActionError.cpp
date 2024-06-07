#include "../include/ActionError.h"

std::string ActionError::toStdString() const{
	return errorTypeToStdString(e);
}

bool ActionError::operator==(const ActionError &other) const {
	return e == other.e;
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

bool ActionBuildError::operator==(const ActionError &other) const {
	const ActionBuildError* otherBuildError = dynamic_cast<const ActionBuildError*>(&other);
	if (otherBuildError) {
		return ActionError::operator==(other) && xmlLineNumber == otherBuildError->xmlLineNumber;
	}
}

ActionBuildError& ActionBuildError::operator=(const ActionBuildError &other) {
	this->e = other.e;
	this->xmlLineNumber = other.xmlLineNumber;
	return *this;
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

bool ActionPerformError::operator==(const ActionError &other) const {
	const ActionPerformError* otherPerformError = dynamic_cast<const ActionPerformError*>(&other);
	if (otherPerformError) {
		return ActionError::operator==(other) && actionNumber == otherPerformError->actionNumber;
	}
}

std::string errorTypeToStdString(ActionErrorType e) {
	std::unordered_map<ActionErrorType, std::string> errorTypeToString {
		{NO_OPER_E, "No operands in expression"},
		{INVALID_ARITY, "Invalid number of arguments"},
		{INVALID_OPERAND_FORMAT, "Format error for one of the operands"},
		{INVALID_LENGTH, "The length or size of one of the lines exceeds 1000 characters"},
		{DIVISION_BY_ZERO, "Division by zero"},
		{POW_WITH_FRACTIONAL_PART, "The operand cannot be fractional for pow or fact operations"},
		{NEGATIVE_POW, "Operand cannot be less than zero for pow or fact operations"},
		{INTEGER_PART_OVERFLOW, "Integer overflow"}
	};
	return errorTypeToString[e];
}
