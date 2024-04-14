#pragma once

#include "qregexp"
#include "QString"

#include "string"
#include "stdexcept"
#include "math.h"
#include "iostream"

using namespace std;

#define MAX_ARR_LENGTH 1000

class BigRealNumber {
private:
    short* fractPrt;
    short* intPrt;
    int fractArrLen;
    int intArrLen;

    int intPrtLen;
    int fractPrtLen;
    bool isNegative;

    //---методы для работы с частями (массивами)----
    short atFract(int ind);
    short atInt(int ind);
    bool appendToFract(short n);
    void appendToInt(short n);
    void doubleFractArr();
    void doubleIntArr();
    //-----------------------------------------------

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

    static BigRealNumber fromStdString(const string& numb);
    static bool validateStdString(const string& numb);
    static bool validateQString(const QString& numb);

    // Конструктор по целому числу
    BigRealNumber(int n);

    BigRealNumber();

    ~BigRealNumber();

    // Получить длину целой части
    int getIntPrtLen() const;
    // Получить длину дробной части
    int getFractPrtLen() const;


    // Перевод в строковой представление числа дробную и целую части
    string toStdString() const;

    // Перегрузка оператора присваивания (=)
    BigRealNumber& operator=(const BigRealNumber &other);
    BigRealNumber& operator=(bool bl);

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
    BigRealNumber pow(BigRealNumber pw) const;

    // Вычисления факториала
    BigRealNumber factorial() const;
};

short* toNewArr(short* oldArr, int oldArrLength, int newArrLength);
void arrShift(short* arr, int len, int shift, bool toRight, int fillVal);
int getFirstNotZero(short* arr, int start, int stop, bool backward);
