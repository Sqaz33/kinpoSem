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

    void appendToInt(short number);
    bool appendToFract(short number);
    int getFirstNotZero(const string& numb, int start, int stop, bool revers);

    short addArraysToBRL(
        const BigRealNumber& term1,
        const BigRealNumber& term2,
        BigRealNumber& res,
        bool addToFract,
        bool minusTerm2,
        short transfer
    ) const;
public:
    BigRealNumber(const BigRealNumber& p);

    BigRealNumber(const string& n);

    BigRealNumber(int n);

    BigRealNumber();

    ~BigRealNumber();

    string toString() const;

    // Перегрузка оператора присваивания (=)
    BigRealNumber& operator=(const BigRealNumber &other);

    // Перегрузка оператора сложения (+)
    BigRealNumber operator+(const BigRealNumber &other) const;

    // Перегрузка оператора вычитания (-)
    BigRealNumber operator-(const BigRealNumber &other) const;

    // Перегрузка оператора умножения (*)
    BigRealNumber operator*(const BigRealNumber &other) const;
    BigRealNumber operator*(int n) const;

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
    BigRealNumber pw(int pow);

    // Вычисления факториала
    BigRealNumber factorial(int fact);
};

#endif //UNTITLED1_BigRealNumber_H
