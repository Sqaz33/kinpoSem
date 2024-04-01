//
// Created by mset6 on 19.02.2024.
//

#ifndef UNTITLED1_BIGREALNUMBER_H
#define UNTITLED1_BIGREALNUMBER_H
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

public:
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
    );

    short attachArrays(
        const BigRealNumber& term1,
        const BigRealNumber& term2,
        BigRealNumber& res,
        bool addToFract,
        bool minusTerm2,
        short transfer
    ) const;

    void appendToInt(short number);

    bool appendToFract(short number, int ind);

    void removeInsignDigits();

    void shiftNumber(int shift, bool toRight);

    void setVal(int n);
public:
    // Конструктор копирования
    BigRealNumber(const BigRealNumber& p);

    // Конструктор объекта по строковому представлению числа
    BigRealNumber(const string& n);

    // Конструкто объекта по целому числу
    BigRealNumber(int n);

    BigRealNumber();

    ~BigRealNumber();

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

    // Перегрузка оператора неравенства (!=)
    bool operator!=(const BigRealNumber &other) const;

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
    BigRealNumber pw(int pow);

    // Вычисления факториала
    BigRealNumber factorial();
};

void arrShift(short* arr, int len, int shift, bool toRight, int fillVal);
int getFirstNotZero(short* arr, int start, int stop, bool backward);

#endif //UNTITLED1_BigRealNumber_H