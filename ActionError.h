#pragma once
#include "unordered_map"
#include "string"

/**
 * @brief Типы ошибок.
*/
enum ActionErrorType {
	NO_OPER_E, // Ошибка создания объекта
	INVALID_ARITY, // Ошибка создания объекта
	INVALID_OPERAND_FORMAT, // Ошибка создания объекта
	INVALID_LENGTH, // Ошибка создания объекта или вычисления
	DIVISION_BY_ZERO, // Ошибка вычисления
	OPERAND_WITH_FRACTIONAL_PART_POW_FACT, // Ошибка вычисления
	OPERAND_LESS_ZERO_POW_FACT // Ошибка вычисления 
};
std::string errorTypeToStdSting(ActionErrorType e);


/**
 * @brief Класс ошибки Action.
*/
class ActionError {
private:
	ActionErrorType e; /** @brief Тип ошибки.*/
public:
	/**
	 * @brief Конструктор ActionError.
	 * @param[in] e тип ошибки.
	*/
	ActionError(ActionErrorType e) : e(e) {};
	/**
	 * @brief Метод получения std::string строкового представления ошибки.
	 * @return std::string строковое представления ошибки.
	*/
	virtual std::string toStdString() const;
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Дочерний класс ActionError.
 *        Класс ошибки создания Action.
*/
class ActionBuildError : public ActionError {
private:
	int xmlLineNumber; /** @brief Строка xml-файла, содержащая ошибочное действие.*/
public:
	/**
	 * @brief Конструктор ActionBuildError.
	 * @param[in] e тип ошибки.
	*/
	ActionBuildError(ActionErrorType e) : ActionError(e), xmlLineNumber(-1) {};
	/**
	 * @brief Сеттер строки xml-файла, содержащей ошибочное действие.
	 * @param[in] ln строка xml-файла.
	*/
	void setXmlLineNumber(int ln);
	std::string toStdString() const override;
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Дочерний класс ActionError.
 *        Класс ошибки выполнения Action.
*/
class ActionPerformError : public ActionError {
private:
	int actionNumber; /** @brief Номер объекта Action, который вызывал ошибку.*/
public:
	/**
	 * @brief Конструктор ActionPerformError.
	 * @param[in] e тип ошибки.
	*/
	ActionPerformError(ActionErrorType e) : ActionError(e), actionNumber(-1) {};
	std::string toStdString() const override;
	/**
	 * @brief Сеттер номера объекта Action, который вызвал ошибку.
	 * @param[in] a номер 
	*/
	void setActionNumber(int a);
};

