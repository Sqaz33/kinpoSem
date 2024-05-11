#pragma once

#include "unordered_map"
#include "string"
#include "sstream"
#include "QString"

#include "BigRealNumber.h"
#include "ActionError.h"

//----------------------Работа с операциями----------------------------

/**
 * @brief Список операций 
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
 * @brief Функция для получения перечисляемой 
 *        операции по строковому представлению операции.
 * @param[in] oper строковое представление операции.
 * 
 * @return Операция из перечисления Operation
 * 
 * @remark Функция вернет Operation.NO_OPER при отсутствии
 *	       соответствующего строкового представления
 *
*/
Operation operFromStdString(const string& oper);

/**
 * @relates Operation
 *
 * @brief Функция для получения строкового представления 
		  операции по операции из перечисления Operation
 * @param[in] oper операция из перечисления Operation
 * @return Строковое представление операции
*/
string stdStringFromOper(Operation oper);
//--------------------------------------------------------------------------

/**
 * @brief Класс для представления действия.
 *
 * @sa
 * ---------------
 * Пример действия:
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
	 * @brief Конструктор Action.
	 * @param[in] oper строковое представление операций.
	 * @param[in] term1 строковое представление первого операнда.
	 * @param[in] term2 строковое представление второго операнда.
	 * 
	 * @exception ActionBuildError если неверное количество операндов
	*/
	Action(Operation oper, const BigRealNumber* term1, const BigRealNumber* term2);

	/**
	 * @brief Метод для вычисления действия.
	 * @return Результат вычисления.
	*/
	BigRealNumber perform() const;

	/**
	 * @brief Функция для получения строкового представления действия.
	 * @return Строковое представление действия.
	*/
	string toStdString() const;

private:
	BigRealNumber term1; /**@brief Первый операнд.*/
	BigRealNumber term2; /**@brief Второй операнд.*/
	Operation oper; /**@brief Операция.*/
	int termCount;  /**@brief Количество операндов*/

	/**
	 * @brief Функция для проверки арности действия.
	 * @return Верно ли арность действия.
	*/
	bool checkArity();
};

