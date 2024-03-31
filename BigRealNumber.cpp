#include "BigRealNumber.h"

BigRealNumber::BigRealNumber(const BigRealNumber& p) {
    isNegative = p.isNegative;
    fractPrtLen = p.fractPrtLen;
    intPrtLen = p.intPrtLen;

    this->fractPrt = new short[1000] {};
    this->intPrt = new short[1000] {};

    for (int i = 0; i < fractPrtLen; i++) {
        this->fractPrt[i] = p.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        this->intPrt[i] = p.intPrt[i];
    }
}

BigRealNumber::BigRealNumber(const string &numb) {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
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
        fractPrt[i] = (short)(numb.at(j) - '0');
    }
  
    removeInsignDigits();
}

BigRealNumber::BigRealNumber(int n) {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
    fractPrtLen = 0;
    intPrtLen = 0;
    isNegative = n < 0;
    
    while (n > 0) {
        intPrt[intPrtLen++] = (short)n % 10;
        n /= 10;
    }
}

BigRealNumber::BigRealNumber() {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
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

    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};

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
                   false, trans);

    res.removeInsignDigits();
    return res;
}

BigRealNumber BigRealNumber::operator+(int n) const {
    return *this + BigRealNumber(n);
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

BigRealNumber BigRealNumber::operator-(int n) const {
    return *this - BigRealNumber(n);
}

BigRealNumber BigRealNumber::operator*(const BigRealNumber& other) const {
    BigRealNumber oth = other;
    BigRealNumber ths = *this;
    oth.isNegative = false;
    ths.isNegative = false;

    // умножить на целую часть
    BigRealNumber resForInt{};
    // прибавлять к ответу множиемое пока целая часть множителя > 0
    oth.fractPrtLen = 0;
    oth.fractPrt = new short[1000] {};
    short* a = oth.fractPrt;
    while (oth > 0) {
        resForInt = resForInt + ths;
        oth = oth - 1;
    }

    BigRealNumber res = resForInt;
    res.isNegative = !(isNegative == other.isNegative);

    if (!other.fractPrtLen) {
        return res;
    }
    // умножить на дробную часть
    BigRealNumber resForFract{};
    // умножать множитель на 10, пока он имеет дробную часть
    oth = other;
    oth.intPrt = a;
    oth.intPrtLen = 0;
    oth.isNegative = false;
    int p = 0;
    while (oth.fractPrtLen) {
        oth = oth * 10;
        p++;
    }
    // умножить на полученный множитель
    resForFract = ths * oth;
    // поделить на 10**p
    resForFract = resForFract / pow(10, p);

    // сложить
    res = res + resForFract;
    return res;
}

BigRealNumber BigRealNumber::operator*(int n) const {
    return *this * BigRealNumber(n);
}

BigRealNumber BigRealNumber::operator/(const BigRealNumber& other) const {
    BigRealNumber oth = other;
    BigRealNumber ths = *this;
    oth.isNegative = false;
    ths.isNegative = false;

    while (oth.fractPrtLen || ths.fractPrtLen) {
        oth = oth * 10;
        ths = ths * 10;
    }

    BigRealNumber quotient(0);
    string p = "1.0";
    int it = 0;
    while (it < 1000 && ths > 0) {
        if (ths < oth) {
            ths = ths * 10;
            if (p == "1.0") {
                p = "0.1";
            } else {
                string cp = p.substr(2);
                p = "0.0" + cp;
            }
            it++;
        } else {
            ths = ths - oth;
            quotient = quotient + BigRealNumber(p);
        }
    }
    quotient.isNegative = !(isNegative == other.isNegative);
    
    return quotient;
}

BigRealNumber BigRealNumber::operator/(int n) const {
    return *this / BigRealNumber(n);
}

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

bool BigRealNumber::operator>(int other) const {
    return *this > BigRealNumber(other);
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

BigRealNumber BigRealNumber::pw(int pow) {
    BigRealNumber res(1);
    if (pow == 0) {
        return res;
    }

    while (pow > 0) {
        res = res * *this;
        pow--;
    }
    return res;
}

BigRealNumber BigRealNumber::factorial() {
    BigRealNumber res(1);
    BigRealNumber fact(1);
    if (*this == 0) {
        return res;
    }

    while (fact <= *this) {
        res = res * fact;
        fact = fact + 1;
    }
    return res;
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

void BigRealNumber::removeInsignDigits() {
    int signDigit = getFirstNotZero(intPrt, 999, -1, true);
    intPrtLen = signDigit + 1;
    signDigit = getFirstNotZero(fractPrt, 999, -1, true);
    fractPrtLen = signDigit + 1;
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

//----------------------------------------------------------------
int getFirstNotZero(short* arr, int start, int stop, bool backward) {
    for (int i = start; i != stop; i += pow(-1, backward)) {
        if (arr[i]) {
            return i;
        }
    }
    return -1;
}