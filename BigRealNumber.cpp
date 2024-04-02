#include "BigRealNumber.h"

BigRealNumber::BigRealNumber(const BigRealNumber& p) {
    int len = max(this->fractPrtLen, p.fractPrtLen);
    for (int i = 0; i < len; i++) {
        this->fractPrt[i] = p.fractPrt[i];
    }
    len = max(this->intPrtLen, p.intPrtLen);
    for (int i = 0; i < len; i++) {
        this->intPrt[i] = p.intPrt[i];
    }
    isNegative = p.isNegative;
    fractPrtLen = p.fractPrtLen;
    intPrtLen = p.intPrtLen;
}

BigRealNumber::BigRealNumber(const string& numb) {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
    isNegative = numb.at(0) == '-';

    int point = (int)numb.find('.');
    intPrtLen = point - isNegative;

    fractPrtLen = numb.length() - intPrtLen - 1 - isNegative;

    int j = isNegative ? 1 : 0;
    for (int i = intPrtLen - 1; i >= 0; i--, j++) {
        intPrt[i] = (short)(numb.at(j) - '0');
    }
    j++;

    for (int i = 0; i < fractPrtLen; i++, j++) {
        fractPrt[i] = (short)(numb.at(j) - '0');
    }
    removeInsignDigits();
}

BigRealNumber::BigRealNumber(int n) {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
    isNegative = n < 0;
    setVal(n);
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

BigRealNumber& BigRealNumber::operator=(const BigRealNumber& other) {
    int len = max(this->fractPrtLen, other.fractPrtLen);
    for (int i = 0; i < len; i++) {
        this->fractPrt[i] = other.fractPrt[i];
    }
    len = max(this->intPrtLen, other.intPrtLen);
    for (int i = 0; i < len; i++) {
        this->intPrt[i] = other.intPrt[i];
    }
    isNegative = other.isNegative;
    fractPrtLen = other.fractPrtLen;
    intPrtLen = other.intPrtLen;
    return *this;
}

BigRealNumber BigRealNumber::operator+(const BigRealNumber& other) const {
    BigRealNumber res {};
    add(other, res); 
    return res;
}

BigRealNumber BigRealNumber::operator+(int n) const {
    return *this + BigRealNumber(n);
}


BigRealNumber BigRealNumber::operator-(const BigRealNumber& other) const {
    BigRealNumber res{};
    sub(other, res);
    return res;
}

BigRealNumber BigRealNumber::operator-(int n) const {
    return *this - BigRealNumber(n);
}

BigRealNumber BigRealNumber::operator*(const BigRealNumber& other) const {
    BigRealNumber res{};
    mul(other, res);
    return res;
}

BigRealNumber BigRealNumber::operator*(int n) const {
    return *this * BigRealNumber(n);
}

BigRealNumber BigRealNumber::operator/(const BigRealNumber& other) const {
    return BigRealNumber();
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
    }
    else if (intPrtLen < other.intPrtLen) {
        return false;
    }

    for (int i = intPrtLen - 1; i >= 0; i--) {
        if (intPrt[i] > other.intPrt[i]) {
            return true;
        }
        else if (intPrt[i] < other.intPrt[i]) {
            return false;
        }
    }

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


// ---------------------вспомогательные методы---------------------------
void BigRealNumber::add(
        const BigRealNumber& term2,
        BigRealNumber& res
) const {
    if (!(isNegative) && term2.isNegative) {
        sub(term2, res);
        return;
    }
    else if (isNegative && !term2.isNegative) {
        term2.sub(*this, res);
        return;
    }
    BigRealNumber *rs = this == &res ? new BigRealNumber() : &res;
    rs->isNegative = isNegative;

    short trans = attachArrays(*this, term2,
                                *rs, true,
                                false, 0);
    attachArrays(*this, term2,
                *rs, false,
                false, trans);

    rs->removeInsignDigits();
    if (this == &res) {
        res = *rs;
    }
}

void BigRealNumber::sub(
    const BigRealNumber& subtr,
    BigRealNumber& res
) const {
    if ((isNegative && subtr.isNegative) || (!(isNegative) && subtr.isNegative)) {
        add(subtr, res);
        res.isNegative = isNegative;
        return;
    }
    else if (isNegative && subtr.isNegative) {
        subtr.sub(*this, res);
        return;
    }
    if (*this >= subtr) {
        BigRealNumber *rs = this == &res ? new BigRealNumber() : &res;
        short trans = attachArrays(*this, subtr,
                                    *rs, true,
                                    true, 0);
        attachArrays(*this, subtr,
                      *rs, false,
                      true, trans);
        rs->removeInsignDigits();
        if (this == &res) {
            res = *rs;
        }
    } else {
        subtr.sub(*this, res);
    }
}

void BigRealNumber::mul(
    const BigRealNumber& fac,
    BigRealNumber &res
) const {
    // умножаем на цифру
    if (fac.intPrtLen == 1 && !fac.fractPrtLen) {
        short ref = 0;
        short f = fac.intPrt[0];
        for (int i = fractPrtLen - 1; i >= 0; i--) {
            short n = fractPrt[i] * f + ref;
            ref = n / 10;
            n %= 10;
            res.appendToFract(n, i);
        }  
        for (int i = 0; i < intPrtLen; i++) {
            short n = intPrt[i] * f + ref;
            ref = n / 10;
            n %= 10;
            res.appendToInt(n);
        }
        if (ref) {
            res.appendToInt(ref);
        }
        return;
    }
    
    BigRealNumber buf1{};
    for (int i = fac.fractPrtLen - 1; i >= 0; i--) {
        buf1.setVal(fac.fractPrt[i]);
        mul(buf1, buf1);
        buf1.shiftNumber(i + 1, true);
        res.add(buf1, res);
    }
    for (int i = 0; i < fac.intPrtLen; i++) {
        buf1.setVal(fac.intPrt[i]);
        mul(buf1, buf1);
        buf1.shiftNumber(i, false);
        res.add(buf1, res);
    }
}

short BigRealNumber::attachArrays(
    const BigRealNumber& term1,
    const BigRealNumber& term2,
    BigRealNumber& res,
    bool addToFract,
    bool minusTerm2,
    short transfer
) const {
    int start;
    int stop;
    int diff;
    short* t1;
    short* t2;

    if (addToFract) {
        start = max(term1.fractPrtLen, term2.fractPrtLen) - 1;
        start = max(0, start);
        stop = 0;
        diff = -1;
        t1 = term1.fractPrt;
        t2 = term2.fractPrt;
    }
    else {
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
            if (!res.appendToFract(n, i)) {
                break;
            }
        }
        else {
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

void BigRealNumber::appendToInt(short number) {
    if (intPrtLen + 1 >= 1000) {
        throw runtime_error("Ошибка вычисления: целая часть "
            "выходного числа содержит более 1000 цифр");
    }
    intPrt[intPrtLen++] = number;
}

bool BigRealNumber::appendToFract(short number, int ind) {
    if (fractPrtLen + 1 >= 1000 || ind >= 1000) {
        return false;
    }
    fractPrt[ind] = number;
    fractPrtLen++;
    return true;
}


void BigRealNumber::removeInsignDigits() {
    int signDigit = getFirstNotZero(intPrt, 999, -1, true);
    intPrtLen = signDigit + 1;
    signDigit = getFirstNotZero(fractPrt, 999, -1, true);
    fractPrtLen = signDigit + 1;
}

void BigRealNumber::shiftNumber(int shift, bool toRight) {
    while (shift) {
        short buf = toRight ? intPrt[0] : fractPrt[0];
        if (intPrtLen || !toRight) {
            if (!toRight) {
                intPrtLen++;
            }
            arrShift(intPrt, intPrtLen, 1, !toRight, 0);
            if (toRight && intPrtLen) {
                intPrtLen--;
            }
        }
        if (fractPrt || toRight) {
            if (toRight) {
                if (intPrtLen + 1 >= 1000) {
                    throw runtime_error("Ошибка вычисления: целая часть "
                        "выходного числа содержит более 1000 цифр");
                }
                fractPrtLen++;
            }
            arrShift(fractPrt, fractPrtLen, 1, toRight, 0);
            if (!toRight && fractPrtLen) {
                fractPrtLen--;
            }
        }
        if (toRight) {
            fractPrt[0] = buf;
        } else {
            intPrt[0] = buf;
        }
        shift--;
    }
}

void BigRealNumber::setVal(int n) {
    for (int i = 0; i < max(intPrtLen, fractPrtLen); i++) {
        intPrt[i] = 0;
        fractPrt[i] = 0;
    }
    intPrtLen = 0;
    fractPrtLen = 0;
    while (n > 0) {
        intPrt[intPrtLen++] = (short)n % 10;
        n /= 10;
    }
}


// -------------------------------------------внеклассовые функции
void arrShift(short* arr, int len, int shift, bool toRight, int fillVal) {
    if (!len) {
        return;
    }
    shift %= len;
    int wp, rp, dif, stop;
    if (toRight) {
        wp = len - 1;
        rp = wp - shift;
        dif = -1;
        stop = -1;
    } else {
        wp = 0;
        rp = wp + shift;
        dif = 1;
        stop = len;
    }
    while (rp != stop) {
        arr[wp] = arr[rp];
        arr[rp] = fillVal;
        wp += dif;
        rp += dif;
    }
    
}

int getFirstNotZero(short* arr, int start, int stop, bool backward) {
    for (int i = start; i != stop; i += pow(-1, backward)) {
        if (arr[i]) {
            return i;
        }
    }
    return -1;
}
