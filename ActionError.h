#pragma once
#include "unordered_map"
#include "string"

/**
 * @brief ���� ������.
*/
enum ActionErrorType {
	NO_OPER_E, // ������ �������� �������
	INVALID_ARITY, // ������ �������� �������
	INVALID_OPERAND_FORMAT, // ������ �������� �������
	INVALID_LENGTH, // ������ �������� ������� ��� ����������
	DIVISION_BY_ZERO, // ������ ����������
	OPERAND_WITH_FRACTIONAL_PART_POW_FACT, // ������ ����������
	OPERAND_LESS_ZERO_POW_FACT // ������ ���������� 
};
std::string errorTypeToStdSting(ActionErrorType e);


/**
 * @brief ����� ������ Action.
*/
class ActionError {
private:
	ActionErrorType e; /** @brief ��� ������.*/
public:
	/**
	 * @brief ����������� ActionError.
	 * @param[in] e ��� ������.
	*/
	ActionError(ActionErrorType e) : e(e) {};
	/**
	 * @brief ����� ��������� std::string ���������� ������������� ������.
	 * @return std::string ��������� ������������� ������.
	*/
	virtual std::string toStdString() const;
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief �������� ����� ActionError.
 *        ����� ������ �������� Action.
*/
class ActionBuildError : public ActionError {
private:
	int xmlLineNumber; /** @brief ������ xml-�����, ���������� ��������� ��������.*/
public:
	/**
	 * @brief ����������� ActionBuildError.
	 * @param[in] e ��� ������.
	*/
	ActionBuildError(ActionErrorType e) : ActionError(e), xmlLineNumber(-1) {};
	/**
	 * @brief ������ ������ xml-�����, ���������� ��������� ��������.
	 * @param[in] ln ������ xml-�����.
	*/
	void setXmlLineNumber(int ln);
	std::string toStdString() const override;
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief �������� ����� ActionError.
 *        ����� ������ ���������� Action.
*/
class ActionPerformError : public ActionError {
private:
	int actionNumber; /** @brief ����� ������� Action, ������� ������� ������.*/
public:
	/**
	 * @brief ����������� ActionPerformError.
	 * @param[in] e ��� ������.
	*/
	ActionPerformError(ActionErrorType e) : ActionError(e), actionNumber(-1) {};
	std::string toStdString() const override;
	/**
	 * @brief ������ ������ ������� Action, ������� ������ ������.
	 * @param[in] a ����� 
	*/
	void setActionNumber(int a);
};

