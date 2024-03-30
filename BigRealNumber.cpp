#include "BigRealNumber.h"

BigRealNumber::BigRealNumber(const BigRealNumber& p) {
    isNegative = p.isNegative;
    fractPrtLen = p.fractPrtLen;
    intPrtLen = p.intPrtLen;

    this->fractPrt = new short[1000];
    fillArrayWithZero(this->fractPrt, 1000);
    this->intPrt = new short[1000];
    fillArrayWithZero(this->intPrt, 1000);

    for (int i = 0; i < fractPrtLen; i++) {
        this->fractPrt[i] = p.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        this->intPrt[i] = p.intPrt[i];
    }
}

BigRealNumber::BigRealNumber(const string &numb) {
    intPrt = new short[1000];
    fillArrayWithZero(intPrt, 1000);
    fractPrt = new short[1000];
    fillArrayWithZero(fractPrt, 1000);
    isNegative = numb[0] == '-';

    int point = (int) numb.find('.');

    intPrtLen = point;
    fractPrtLen = numb.length() - intPrtLen - 1;
    if (isNegative) {
        intPrt--;
    }

    // копирование целой части
    int j = isNegative ? 1 : 0;
    for (int i = intPrtLen - 1; i >= 0; i--, j++) {
        intPrt[i] = (short)(numb.at(j) - '0');
    }
    j++;
    // копирование дробной части
    for (int i = 0; i < fractPrtLen; i++, j++) {
        fractPrt[j] = (short)(numb.at(j) - '0');
    }
    removeInsignDigits();
}

BigRealNumber::BigRealNumber(int n) {
    intPrt = new short[1000];
    fillArrayWithZero(intPrt, 1000);
    fractPrt = new short[1000];
    fillArrayWithZero(fractPrt, 1000);

    fractPrtLen = 0;
    isNegative = n < 0;
    
    int a[1000];
    int len = 0;
    while (n > 0) {
        a[len++] = n % 10;
        n /= 10;
    }
    intPrtLen = len;

    for (int i = 0, j = len  - 1; j >= 0; i++, j--) {
        intPrt[i] = a[j];
    }
}

BigRealNumber::BigRealNumber() {
    intPrt = new short[1000];
    fillArrayWithZero(intPrt, 1000);
    fractPrt = new short[1000];
    fillArrayWithZero(fractPrt, 1000);
    intPrtLen = 0;
    fractPrtLen = 0;
    isNegative = false;
}

BigRealNumber::~BigRealNumber() {
    delete fractPrt;
    delete intPrt;
}

string BigRealNumber::toString() const {
    string numb;
    if (isNegative) {
        numb.append(1, '-');
    }
    for (int i = intPrtLen - 1; i >= 0; i--) {
        numb.append(1, (char)('0' + (int)intPrt[i]));
    }
    if (!intPrtLen) {
        numb.append(1, '0');
    }
    numb.append(1, '.');
    for (int i = 0; i < fractPrtLen; i++) {
        numb.append(1, (char)('0' + (int)fractPrt[i]));
    }
    if (!fractPrtLen) {
        numb.append(1, '0');
    }
    return numb;
}

//-----------------------------------------------------
BigRealNumber &BigRealNumber::operator=(const BigRealNumber &other) {
    isNegative = other.isNegative;
    fractPrtLen = other.fractPrtLen;
    intPrtLen = other.intPrtLen;

    this->fractPrt = new short[1000];
    fillArrayWithZero(this->fractPrt, 1000);
    this->intPrt = new short[1000];
    fillArrayWithZero(this->intPrt, 1000);

    for (int i = 0; i < fractPrtLen; i++) {
        this->fractPrt[i] = other.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        this->intPrt[i] = other.intPrt[i];
    }

    return *this;
}

BigRealNumber BigRealNumber::operator+(const BigRealNumber &other) const {
    // this + other
    // -this + other
    // this + (-other)
    // -this + (-other)

    if (!(isNegative) && other.isNegative) { // this + (-other)
        return *this - other;
    } else if (isNegative && !other.isNegative) { // -this + other
        return other - *this;
    }

    // this + other
    // -this + (-other)
    BigRealNumber res{};
    res.isNegative = isNegative;

    // сложение дробных частей
    short trans = attachArrays(*this, other,
                                 res, true,
                                 false, 0);
    // сложение целых частей
    attachArrays(*this, other,
                   res, false,
                   true, trans);

    return res;
}

BigRealNumber BigRealNumber::operator-(const BigRealNumber &other) const {
    // this - other
    // -this - other
    // -this - (-other)
    // this - (-other)

    BigRealNumber res{};
    if ((isNegative && other.isNegative) || (!(isNegative) && other.isNegative)) {
        // -this - other; 
        // this - (-other) = this + other
        res = *this + other;
        res.isNegative = isNegative;
        return  res;
    } else if (isNegative && other.isNegative) {
        // -this - (-other) = other - this
        res = other;
        res = res - *this;
        return res;
    }

    // this - other
    if (*this >= other) {
        short trans = attachArrays(*this, other,
                                    res, true,
                                    true, 0);
        attachArrays(*this, other,
                     res, false,
                     true, trans);
        res.removeInsignDigits();
        return res;
    } else {
        res = other - *this;
        res.isNegative = true;
        return res;
    }
}
// доделать
BigRealNumber BigRealNumber::operator*(const BigRealNumber& other) const {
    // умножить на целую часть
    // прибавлять к ответу множиемое пока целая часть множителя > 0
    BigRealNumber cp = other;
    BigRealNumber zero(0);
    BigRealNumber one(1);
    BigRealNumber res;

    cp.fractPrtLen = 0;
    while (cp > zero) {
        res = res + *this;
        cp = cp - one;
    }

    // умножить на дробную часть
    // умножать множитель на 10, пока он имеет 
    // умножить множиемое на множитель
    // поделить множиемое, на 10**кол. для умножение множителя

    // сложить
    return res;
}

BigRealNumber BigRealNumber::operator*(int n) const {
    return *this * BigRealNumber(10);
}

//BigRealNumber BigRealNumber::operator/(const BigRealNumber& other) const {
//
//}

bool BigRealNumber::operator==(const BigRealNumber& other) const {
    if (fractPrtLen != other.fractPrtLen ||
        intPrtLen != other.intPrtLen ||
        isNegative != other.isNegative) 
    {
        return false;
    }
    for (int i = 0; i < fractPrtLen; i++) {
        if (fractPrt[i] != other.fractPrt[i]) {
            return false;
        }
    }
    for (int i = 0; i < intPrtLen; i++) {
        if (intPrt[i] != other.intPrt[i]) {
            return false;
        }
    }
    return true;
}

bool BigRealNumber::operator!=(const BigRealNumber& other) const {
    return !(*this == other);
}

bool BigRealNumber::operator<(const BigRealNumber& other) const {
    return *this != other && !(*this > other);
}

bool BigRealNumber::operator>(const BigRealNumber& other) const {
    if (intPrtLen > other.intPrtLen) {
        return true;
    } else if (intPrtLen < other.intPrtLen) {
        return false;
    }

    // сравниваем целые части, длинны равны
    for (int i = intPrtLen - 1; i >= 0; i--) {
        if (intPrt[i] > other.intPrt[i]) {
            return true;
        } else if (intPrt[i] < other.intPrt[i]) {
            return false;
        }
    }
    
    // сравниваем дробные части
    bool isEqual = true;
    for (int i = 0; i < fractPrtLen; i++) {
        if (isEqual) {
            isEqual = fractPrt[i] == other.fractPrt[i];
        }
        if (fractPrt[i] > other.fractPrt[i]) {
            return true;
        }
        else if (fractPrt[i] < other.fractPrt[i]) {
            return false;
        }
    }

    if (isEqual && other.fractPrtLen > fractPrtLen) {
        return false;
    }
    
    return *this != other;
}

bool BigRealNumber::operator<=(const BigRealNumber& other) const {
    if (*this == other) {
        return true;
    }
    return *this < other;
}

bool BigRealNumber::operator>=(const BigRealNumber& other) const {
    if (*this == other) {
        return true;
    }
    return *this > other;
}

// -------- вспомогательные методы --------------
void BigRealNumber::fillArrayWithZero(short* arr, int len) {
    for (int i = 0; i < len; i++) {
        arr[i] = 0;
    }
}

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

void BigRealNumber::removeInsignDigits() {
    int signDigit = getFirstNotZero(intPrt, 999, 0, true);
    intPrtLen = signDigit + 1;
    signDigit = getFirstNotZero(fractPrt, 999, 0, true);
    fractPrtLen = signDigit + 1;
}

int BigRealNumber::getFirstNotZero(short* arr, int start, int stop, bool backward) {
    for (int i = start; i != stop; i += pow(-1, backward)) {
        if (arr[i]) {
            return i;
        }
    }
    return -1;
}

short BigRealNumber::attachArrays(
        const BigRealNumber &term1,
        const BigRealNumber &term2,
        BigRealNumber &res,
        bool addToFract,
        bool minusTerm2,
        short transfer
) const {
    int start;
    int stop;
    int diff;
    short *t1;
    short *t2;

    if (addToFract) {
        start = max(term1.fractPrtLen, term2.fractPrtLen) - 1;
        start = max(0, start);
        stop = 0;
        diff = -1;
        t1 = term1.fractPrt;
        t2 = term2.fractPrt;
    } else {
        start = 0;
        stop = max(term1.intPrtLen, term2.intPrtLen) - 1;
        stop = max(0, stop);
        diff = 1;
        t1 = term1.intPrt;
        t2 = term2.intPrt;
    }

    for (int i = start; ; i += diff) {
        short n = transfer;
        n += t1[i] + t2[i] * pow(-1, minusTerm2);
        transfer = n > 9;
        if (n < 0) {
            n += 10;
            transfer = -1;
        }
        n %= 10;

        if (addToFract) {
            if (!res.appendToFract(n)) {
                break;
            }
        } else {
            res.appendToInt(n);
        }
        if (i == stop) {
            break;
        }
    }

    if (transfer > 0 && !addToFract) {
        res.appendToInt(transfer);
    }

    return transfer;
}
