#pragma once

#include "unordered_map"
#include "string"
#include "sstream"
#include "QString"

#include "BigRealNumber.h"
#include "ActionError.h"

//----------------------������ � ����������----------------------------

/**
 * @brief ������ �������� 
*/
enum Operation {
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
	NO_LESS,
	NO_OPER
};

/**
 * @relates Operation 
 * 
 * @brief ������� ��� ��������� ������������� 
 *        �������� �� ���������� ������������� ��������.
 * @param[in] oper ��������� ������������� ��������.
 * 
 * @return �������� �� ������������ Operation
 * 
 * @remark ������� ������ Operation.NO_OPER ��� ����������
 *	       ���������������� ���������� �������������
 *
*/
Operation operFromStdString(const string& oper);

/**
 * @relates Operation
 *
 * @brief ������� ��� ��������� ���������� ������������� 
		  �������� �� �������� �� ������������ Operation
 * @param[in] oper �������� �� ������������ Operation
 * @return ��������� ������������� ��������
*/
string stdStringFromOper(Operation oper);
//--------------------------------------------------------------------------

/**
 * @brief ����� ��� ������������� ��������.
 *
 * @sa
 * ---------------
 * ������ ��������:
 * 1 + 2 = 3
 * term1 = 1
 * term2 = 2
 * oper = '+
 * perform - '='
 * 3 - perform return
 * --------------------
 *
*/
class Action {
public:
	/**
	 * @brief ����������� Action.
	 * @param[in] oper ��������� ������������� ��������.
	 * @param[in] term1 ��������� ������������� ������� ��������.
	 * @param[in] term2 ��������� ������������� ������� ��������.
	 * 
	 * @exception ActionBuildError ���� �������� ���������� ���������
	*/
	Action(Operation oper, const BigRealNumber* term1, const BigRealNumber* term2);

	/**
	 * @brief ����� ��� ���������� ��������.
	 * @return ��������� ����������.
	*/
	BigRealNumber perform() const;

	/**
	 * @brief ������� ��� ��������� ���������� ������������� ��������.
	 * @return ��������� ������������� ��������.
	*/
	string toStdString() const;

private:
	BigRealNumber term1; /**@brief ������ �������.*/
	BigRealNumber term2; /**@brief ������ �������.*/
	Operation oper; /**@brief ��������.*/
	int termCount;  /**@brief ���������� ���������*/

	/**
	 * @brief ������� ��� �������� ������� ��������.
	 * @return ����� �� ������� ��������.
	*/
	bool checkArity();
};

