#pragma once

#include <qregexp>
#include <QString>

#include "string"
#include "stdexcept"
#include "math.h"
#include "iostream"

#include "ActionError.h"

using namespace std;

/**
 * @brief Класс для представления вещественных чисел массивом своих цифр.
 * Далее BigRealNumber - BRN.
*/
class BigRealNumber {
private:
    short* intPrt; /**@brief Массив целой части.*/
    short* fractPrt; /**@brief Массив дробной части.*/

    int intPrtLen; /**@brief Длина целой части.*/
    int fractPrtLen; /**@brief Длина дробной части.*/
    bool isNegative; /**@brief Флаг, указывающий, является ли данное число отрицательным.*/

public:
    // Доступ к внутренним полям для целей тестирования
    //=====================================================
    const short* getIntPrt() const { return intPrt; }
    const short* getFractPrt() const { return fractPrt; }
    //=====================================================
    
    /**
     * @brief Конструктор копирования.
     * @param[in] p копируемый объект BRN.
    */
    BigRealNumber(const BigRealNumber& p);

    /**
     * @brief Конструктор по целому числу.
     * @param[in] n целое число. 
    */
    BigRealNumber(int n);

    /**
     * @brief Конструктор "пустого" объекта.
    */
    BigRealNumber();

    /**
     * @brief Деструктор BRN.
    */
    ~BigRealNumber();

    /**
     * @brief Метод порождающий BRN по строковому представлению действительного числа.
     * @param[in] numb строковое представление числа:
     * 
     * @pre
     * Требования к numb.
     * numb должно иметь вид "знак[целая_часть]разделяющий_символ[дробная_часть]".
     * 
     * Знак: число отрицательно -> numb[0] == '-', число положительно -> numb[0] - цифра целой части.
     * 
     * Целая_часть: max(length) = 1000, min(length) - 1. 
     * 
     * Разделяющий_символ: символ '.' точки.
     * 
     * Дробная_часть: max(length) = 1000, min(length) - 1. 
     * 
     * Дробная и целые части должны содержать лишь символы цифр (0-9).
     * 
     * numb - должно содержать только следующие символы: цифры {'-', ('0'-'9'), '.',}
     * 
     * @return Объект BRN.
     * 
     * @exception ActionBuildError если строковое представление numb числа не соответствует требованиям.
    */
    static BigRealNumber fromStdString(const string& numb);

    /**
     * @brief Метод валидирующий std::string строковое представление числа,
     * показывает, возможно ли создать по этой строки объект BRN.
     * 
     * @param[in] numb строковое представление числа.
     * @return Возможно ли создать объект BRN по данной std::string строке.
    */
    static bool validateStdString(const string& numb);
    /**
     * @brief Метод валидирующий QString строковое представление числа,
     * показывает, возможно ли создать по этой строки объект BRN.
     *
     * Например: "-5.0", "0.3".
     *
     * @param[in] numb строковое представление числа.
     * @return Возможно ли создать объект BRN по данной QString строке.
    */
    static bool validateQString(const QString& numb);


    /**
     * @brief Метод для получения длины целой части числа.
     * @return Длинна целой части числа.
    */
    int getIntPrtLen() const;
    /**
     * @brief Метод для получения длины части числа.
     * @return Длинна целой части числа.
    */
    int getFractPrtLen() const;

    /**
     * @brief Метод для получения занака числа.
     * @return Знак числа.
    */
    bool negative() const;


    /**
     * @brief Метод для перевода в std::string строковое представление числа.
     * @return std::string строковое представление числа.
    */
    string toStdString() const;

    /**
     * @brief Метод перегрузки оператора присваивания (=).
     * @param[in] other объект BRN.
     * @return Новый объект BRN.
    */
    BigRealNumber& operator=(const BigRealNumber &other);
    /**
     * @brief Метод перегрузки оператора присваивания (=) по булевому значению.
     * @param[in] bl булевое значение.
     * @return Новый объект BRN.
    */
    BigRealNumber& operator=(bool bl);

    /**
     * @brief Метод перегрузки оператора сложения (+).
     * @param[in] other второе слагаемое.
     * @return Результат сложения.
    */
    BigRealNumber operator+(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора сложения (+).
     * @param[in] other второе слагаемое.
     * @return Результат сложения.
    */
    BigRealNumber operator+(int other) const;

    /**
     * @brief Метод перегрузки оператора вычитания (-).
     * @param[in] other вычитаемое.
     * @return Результат вычитания.
    */
    BigRealNumber operator-(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора вычитания (-).
     * @param[in] other вычитаемое.
     * @return Результат вычитания.
    */
    BigRealNumber operator-(int n) const;

    /**
     * @brief Метод перегрузки оператора умножения (*).
     * @param[in] other множитель.
     * @return Результат умножения.
    */
    BigRealNumber operator*(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора умножения (*).
     * @param[in] other множитель.
     * @return Результат умножения.
    */
    BigRealNumber operator*(int n) const;

    /**
     * @brief Метод перегрузки оператора деления (/).
     * @param[in] other делитель.
     * @return Результат деления.
    */
    BigRealNumber operator/(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора деления (/).
     * @param[in] other делитель.
     * @return Результат деления.
    */
    BigRealNumber operator/(int n) const;

    /**
     * @brief Метод перегрузки оператора равенства (==).
     * @param[in] other сравниваемый объект BRN.
     * @return Равны ли числа.
    */
    bool operator==(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора равенства (==).
     * @param[in] other сравниваемое число.
     * @return Равны ли числа.
    */
    bool operator==(int other) const;

    /**
     * @brief Метод перегрузки оператора неравенства (!=).
     * @param other сравниваемый объект BRN.
     * @return Не равны ли числа 
    */
    bool operator!=(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора неравенства (!=).
     * @param[in] other сравниваемое число.
     * @return Не равны ли числа.
    */
    bool operator!=(int other) const;

    /**
     * @brief Метод перегрузки оператора меньше (<).
     * @param[in] other сравниваемый объект BRN.
     * @return Меньше ли данное число чем другое.
    */
    bool operator<(const BigRealNumber &other) const;

    /**
     * @brief Метод перегрузки оператора больше (>).
     * @param[in] other сравниваемый объект BRN.
     * @return Больше ли данное число чем другое.
    */
    bool operator>(const BigRealNumber &other) const;
    /**
     * @brief Метод перегрузки оператора больше (>).
     * @param[in] other сравниваемое число.
     * @return Больше ли данное число чем другое.
    */
    bool operator>(int other) const;

    /**
     * @brief Метод перегрузки оператора меньше или равно (<=).
     * @param[in] other сравниваемый объект BRN.
     * @return Меньше или равно ли данное число чем другое.
    */
    bool operator<=(const BigRealNumber &other) const;

    /**
     * @brief Метод перегрузки оператора больше или равно (>=).
     * @param[in] other сравниваемый объект BRN.
     * @return Больше или равно ли данное число чем другое.
    */
    bool operator>=(const BigRealNumber &other) const;

    /**
     * @brief Метод возведения в степень.
     * @param[in] pw степень. 
     * @return Результат возведения в степень.
     * 
     * @pre Метод возводит только в неотрицательную целую степень.
     * @pre pw > 0 && !pw.fractPrt.
     * 
     * @exception ActionPerformError если степень отрицательна.
     * @exception ActionPerformError если степень не целая.
    */
    BigRealNumber pow(BigRealNumber pw) const;

    /**
     * @brief Метод вычисления факториала.
     * @return Результат вычисления факториала.
     *
     * @pre Метод вычисляет факториал только для неотрицательного целочисленного числа. 
     * @pre this > 0 && !this.fractPrt.
     *
     * @exception ActionPerformError если число отрицательно.
     * @exception ActionPerformError если число не целое.
    */
    BigRealNumber factorial() const;

private:
    // short* intPrt; /**@brief Массив целой части.*/
    // short* fractPrt; /**@brief Массив дробной части.*/

    // int intPrtLen; /**@brief Длина целой части.*/
    // int fractPrtLen; /**@brief Длина дробной части.*/
    // bool isNegative; /**@brief Флаг, указывающий, является ли данное число отрицательным.*/

    /**
     * @brief Внутренний метод сложения, 
     *        аналогичный методу operator+ 
     *        из открытого интерфейса.
     * @see operator+
     * @param[in] term2 
     * @param[out] res 
    */
    void add(
        const BigRealNumber& term2,
        BigRealNumber& res
    ) const;

    /**
     * @brief Внутренний метод вычитания,
     *        аналогичный методу operator- 
     *        из открытого интерфейса.
     * @see operator-
     * @param[in] term2
     * @param[out] res
    */
    void sub(
        const BigRealNumber& subtr,
        BigRealNumber& res
    ) const;

    /**
     * @brief Внутренний метод умножения,
     *        аналогичный методу operator*
     *        из открытого интерфейса.
     * @see operator*
     * @param[in] term2
     * @param[out] res
    */
    void mul(
        const BigRealNumber& fac,
        BigRealNumber& res
    ) const;
    
    /**
     * @brief Внутренний метод деления,
     *        аналогичный методу operator/
     *        из открытого интерфейса
     * @see operator/
     * @param[in] term2
     * @param[out] res
    */
    void div(
        const BigRealNumber& diver,
        BigRealNumber& res
    ) const;

    /**
     * @brief Метод для деления с остатком.
     * @param[in] diver делитель.
     * @param[out] R результат деления. 
     * @param[out] Q остаток от деления.
    */
    void divRemaind(
        const BigRealNumber& diver,
        BigRealNumber& R,
        BigRealNumber& Q
    ) const;

    /**
     * @brief Метод для "приложения" массивов
     *        В процессе "прикладывания" происходит вычитание 
     *        или сложение массивов.
     * @param[in] term1 первый операнд.
     * @param[in] term2 второй операнд.
     * @param[out] res результат действия.
     * @param[in] addToFract работать ли с дробными частями.
     * @param[in] minusTerm2 отнимать ли.
     * @param[in] transfer перенос.
     * @return Перенос.
    */
    short attachArrays(
        const BigRealNumber& term1,
        const BigRealNumber& term2,
        BigRealNumber& res,
        bool addToFract,
        bool minusTerm2,
        short transfer
    ) const;

    /**
     * @brief Метод для добавления значения в конец целой части.
     * @param[in] number добавляемое число.
     * 
     * @exception ActionPerformError если переполнение целой части
    */
    void appendToInt(short number);
    
    /**
     * @brief Метод для добавления значение в дробную часть по индексу.
     * @param[in] number добавляемое число.
     * @param[in] ind индекс по которому добавляется число.
     * @return Удачно, ли добавление.
    */
    bool appendToFract(short number, int ind);

    /**
     * @brief Метод для удаления незначащих разрядов.
    */
    void removeInsignDigits();

    /**
     * @brief Метод для сдвига всего числа.
     * 
     * Например:
     * 32.2 >> 1 --> 3.22
     * 
     * @param[in] shift на сколько разрядов сдвигать.
     * @param[in] toRight флаг направления сдвига.
    */
    void shiftNumber(int shift, bool toRight);

    /**
     * @brief Метод для установки целочисленного значения.
     * @param[in] n целочисленное значение.
    */
    void setVal(int n);
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Метод для сдвига массива.
 * @param[in] arr массив.
 * @param[in] len длинна массива.
 * @param[in] shift сдвиг.
 * @param[in] toRight флаг направления сдвига.
 * @param[in] fillVal значение для заполнения.
*/
void arrShift(short* arr, int len, int shift, bool toRight, int fillVal);

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Метод для получения индекса первого ненулевого значения.
 * @param[in] arr массив.
 * @param[in] start начало движения указателя.
 * @param[in] stop конец движения указателя.
 * @param[in] backward флаг направления движения указателя.
 * @return индекс первого ненулевого значения. 
*/
int getFirstNotZero(short* arr, int start, int stop, bool backward);
