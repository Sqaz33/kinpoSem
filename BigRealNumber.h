#pragma once

#include "string"
#include "stdexcept"
#include "math.h"
#include "iostream"

using namespace std;


class BigRealNumber {
private:
    short* intPrt;
    short* fractPrt;

    int intPrtLen;
    int fractPrtLen;
    bool isNegative;

    void add(
        const BigRealNumber& term2,
        BigRealNumber& res
    ) const;

    void sub(
        const BigRealNumber& subtr,
        BigRealNumber& res
    ) const;

    void mul(
        const BigRealNumber& fac,
        BigRealNumber& res
    ) const;

    void div(
        const BigRealNumber& diver,
        BigRealNumber& res
    ) const;

    void divRemaind(
        const BigRealNumber& diver,
        BigRealNumber& R,
        BigRealNumber& Q
    ) const;

    short attachArrays(
        const BigRealNumber& term1,
        const BigRealNumber& term2,
        BigRealNumber& res,
        bool addToFract,
        bool minusTerm2,
        short transfer
    ) const;

    // Добавить значение в конец целой части
    void appendToInt(short number); 
    // Добавить значение в дробную часть по индексу
    bool appendToFract(short number, int ind);
    // Удалить незначащие разряды
    void removeInsignDigits();
    void shiftNumber(int shift, bool toRight);
    void setVal(int n);
public:
    // Конструктор копирования
    BigRealNumber(const BigRealNumber& p);

    // Конструктор по строковому представлению числа
    BigRealNumber(const string& n);

    // Конструктор по целому числу
    BigRealNumber(int n);

    BigRealNumber();

    ~BigRealNumber();

    // Получить длинну целой части
    int getIntPrtLen() const;
    // Получить длинну дробной части
    int getFractPrtLen() const;

    // Перевод в строковой представление числа дробную и целую части
    string toString() const;

    // Перегрузка оператора присваивания (=)
    BigRealNumber& operator=(const BigRealNumber &other);

    // Перегрузка оператора сложения (+)
    BigRealNumber operator+(const BigRealNumber &other) const;
    BigRealNumber operator+(int other) const;

    // Перегрузка оператора вычитания (-)
    BigRealNumber operator-(const BigRealNumber &other) const;
    BigRealNumber operator-(int n) const;

    // Перегрузка оператора умножения (*)
    BigRealNumber operator*(const BigRealNumber &other) const;
    BigRealNumber operator*(int n) const;

    // Перегрузка оператора деления (/)
    BigRealNumber operator/(const BigRealNumber &other) const;
    BigRealNumber operator/(int n) const;

    // Перегрузка оператора равенства (==)
    bool operator==(const BigRealNumber &other) const;
    bool operator==(int other) const;

    // Перегрузка оператора неравенства (!=)
    bool operator!=(const BigRealNumber &other) const;
    bool operator!=(int other) const;

    // Перегрузка оператора меньше (<)
    bool operator<(const BigRealNumber &other) const;

    // Перегрузка оператора больше (>)
    bool operator>(const BigRealNumber &other) const;
    bool operator>(int other) const;

    // Перегрузка оператора меньше или равно (<=)
    bool operator<=(const BigRealNumber &other) const;

    // Перегрузка оператора больше или равно (>=)
    bool operator>=(const BigRealNumber &other) const;

    // Возведение в степень
    BigRealNumber pow(BigRealNumber pw);

    // Вычисления факториала
    BigRealNumber factorial();
};

void arrShift(short* arr, int len, int shift, bool toRight, int fillVal);
int getFirstNotZero(short* arr, int start, int stop, bool backward);
