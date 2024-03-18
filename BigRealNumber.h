//
// Created by mset6 on 19.02.2024.
//

#ifndef UNTITLED1_BIGREALNUMBER_H
#define UNTITLED1_BIGREALNUMBER_H
#include "string"
#include "stdexcept"
using namespace std;

class BigRealNumber {
private:
    short* intPrt;
    short* fractPrt;

    int intPrtLen;
    int fractPrtLen;
    bool isNegative;

    void appendToInt(short number);
    bool appendToFract(short number);
public:
    BigRealNumber();

    BigRealNumber(const string& n);

    string toString() const;

    bool negative() const;

    // Перегрузка оператора сложения (+)
    BigRealNumber operator+(const BigRealNumber &other) const;

    // Перегрузка оператора вычитания (-)
    BigRealNumber operator-(const BigRealNumber &other) const;

    // Перегрузка оператора умножения (*)
    BigRealNumber operator*(const BigRealNumber &other) const;

    // Перегрузка оператора деления (/)
    BigRealNumber operator/(const BigRealNumber &other) const;

    // Перегрузка оператора равенства (==)
    bool operator==(const BigRealNumber &other) const;

    // Перегрузка оператора неравенства (!=)
    bool operator!=(const BigRealNumber &other) const;

    // Перегрузка оператора меньше (<)
    bool operator<(const BigRealNumber &other) const;

    // Перегрузка оператора больше (>)
    bool operator>(const BigRealNumber &other) const;

    // Перегрузка оператора меньше или равно (<=)
    bool operator<=(const BigRealNumber &other) const;

    // Перегрузка оператора больше или равно (>=)
    bool operator>=(const BigRealNumber &other) const;

    // Возведение в степень
    BigRealNumber pow(int pow);

    // Извлечение корня
    BigRealNumber sqrt();

    // Вычисления факториала
    BigRealNumber factorial(int fact);

};

#endif //UNTITLED1_BigRealNumber_H


