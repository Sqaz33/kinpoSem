#include "BigRealNumber.h"

BigRealNumber::BigRealNumber() {
    intPrt = new short[1000];
    fractPrt = new short[1000];
    intPrtLen = 0;
    fractPrtLen = 0;
    isNegative = false;
}

BigRealNumber::BigRealNumber(const string &numb) {
    intPrt = new short[1000];
    fractPrt = new short[1000];

    isNegative = numb[0] == '-';
    intPrtLen = (int) numb.find('.');
    if (isNegative) {
        intPrtLen--;
    }
    fractPrtLen = (int) numb.length() - intPrtLen - 1;
    if (isNegative) {
        fractPrtLen--;
    }

    int j = isNegative ? 1 : 0;
    // копирование целой части
    for (int i = intPrtLen - 1; i >= 0; i--, j++) {
        intPrt[i] = (short) (numb.at(j) - '0');
    }
    j++;

    // копирование дробной части
    for (int i = fractPrtLen - 1; i >= 0; i--, j++) {
        fractPrt[i] = (short) (numb.at(j) - '0');
    }
}

string BigRealNumber::toString() const {
    string numb;
    if (isNegative) {
        numb.append(1, '-');
    }
    for (int i = intPrtLen - 1; i >= 0; i--) {
        numb.append(1, (char) ('0' + (int) intPrt[i]));
    }
    numb.append(1, '.');
    for (int i = fractPrtLen - 1; i >= 0; i--) {
        numb.append(1, (char) ('0' + (int) fractPrt[i]));
    }

    return numb;
}

bool BigRealNumber::negative() const {
    return isNegative;
}

BigRealNumber BigRealNumber::operator+(const BigRealNumber &other) const {
    if (!isNegative && other.negative()) { // this + (-other)
        return *this - other;
    } else if (isNegative) { // -this + other
        return other - *this;
    }

    BigRealNumber res;
    res.isNegative = isNegative;

    // 100.001
    //  90.09

    // 001.100
    // 09.  90

    short trans = 0;
    // сложение дробных частей


    return res;
}

BigRealNumber BigRealNumber::operator-(const BigRealNumber &other) const {

}

// -------- вспомогательные методы --------------
void BigRealNumber::appendToInt(short number) {
    if (intPrtLen + 1 >= 1000) {
        throw runtime_error("Ошибка вычисления: целая часть "
                            "выходного числа содержит более 1000 цифр");
    }
    intPrt[intPrtLen++] = number;
}

bool BigRealNumber::appendToFract(short number) {
    if (fractPrtLen + 1 >= 1000) {
        return false;
    }
    fractPrt[fractPrtLen++] = number;
    return true;

}

