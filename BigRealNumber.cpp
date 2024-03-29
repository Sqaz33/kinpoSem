#include "BigRealNumber.h"

BigRealNumber::BigRealNumber(const BigRealNumber& p) {
    isNegative = p.isNegative;
    fractPrtLen = p.fractPrtLen;
    intPrtLen = p.intPrtLen;

    this->fractPrt = new short[1000];
    this->intPrt = new short[1000];

    for (int i = 0; i < fractPrtLen; i++) {
        this->fractPrt[i] = p.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        this->intPrt[i] = p.intPrt[i];
    }
}

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
        numb.append(1, (char)('0' + (int)intPrt[i]));
    }
    numb.append(1, '.');
    for (int i = fractPrtLen - 1; i >= 0; i--) {
        numb.append(1, (char)('0' + (int)fractPrt[i]));
    }

    return numb;
}

BigRealNumber::~BigRealNumber() {
    delete fractPrt;
    delete intPrt;
}

//-----------------------------------------------------
BigRealNumber &BigRealNumber::operator=(const BigRealNumber &other) {
    isNegative = other.isNegative;
    fractPrtLen = other.fractPrtLen;
    intPrtLen = other.intPrtLen;

    this->fractPrt = new short[1000];
    this->intPrt = new short[1000];

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
    short trans = addArraysToBRL(*this, other,
                                 res, true,
                                 false, 0);
    // сложение целых частей
    addArraysToBRL(*this, other,
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
        short trans = addArraysToBRL(*this, other,
                                      res, true,
                                      true, 0);
        addArraysToBRL(*this, other,
                        res, false,
                        true, trans);
        return res;
    } else {
        res = other - *this;
        res.isNegative = true;
        return res;
    }
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

bool BigRealNumber::operator>(const BigRealNumber& other) const {
    if (intPrtLen > other.intPrtLen) {
        return true;
    }
    else if (intPrtLen < other.intPrtLen) {
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
    // сравниваем дробные части ---------- переделать
    bool fractEqual = true;
    for (int i = fractPrtLen - 1; i >= 0; i--) {
        if (fractEqual) {
            fractEqual = fractPrt[i] == other.fractPrt[i];
        }
        if (fractPrt[i] < other.fractPrt[i]) {
            return false;
        }
    }
    if (fractEqual && other.fractPrtLen > fractPrtLen) {
        return false;
    }
    return true;
}

bool BigRealNumber::operator>=(const BigRealNumber& other) const {
    if (*this == other) {
        return true;
    }
    return *this > other;
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

short BigRealNumber::addArraysToBRL(
        const BigRealNumber &term1,
        const BigRealNumber &term2,
        BigRealNumber &res,
        bool addToFract,
        bool minusTerm2,
        short transfer
) const {
    int len1;
    int len2;
    if (addToFract) {
        len1 = term1.fractPrtLen;
        len2 = term2.fractPrtLen;
    } else {
        len1 = term1.intPrtLen;
        len2 = term2.intPrtLen;
    }

    short *bg; // больший массив
    short *sm; // меньший массив
    // если term2 наименьший массив
    bool minIsTerm2;
    // распределить массивы по длине
    if (len1 > len2) {
        bg = addToFract ? term1.fractPrt : intPrt;
        sm = addToFract ? term2.fractPrt : term2.intPrt;
        minIsTerm2 = true;
    } else {
        bg = addToFract ? term2.fractPrt : term2.intPrt;
        sm = addToFract ? term1.fractPrt : intPrt;
        minIsTerm2 = false;
    }

    // распределить длинны
    if (addToFract) {
        len1 = max(term1.fractPrtLen, term2.fractPrtLen);
        len2 = min(term1.fractPrtLen, term2.fractPrtLen);
    } else {
        len1 = max(term1.intPrtLen, term2.intPrtLen);
        len2 = min(term1.intPrtLen, term2.intPrtLen);
    }

    for (int i = 0, j = 0; i < len1; i++) {
        short n = transfer;
        // при сложении целых частей, начало меньшего массива прикладывается
        // к началу большего
        // при сложении дробных частей, конец меньшего массива прикладывается к
        // концу большего
        // пример 90.90; 1000.001
        // 0001.100
        // 09  . 09
        if ((i < len2 && !addToFract) || (i >= len1 - len2 && addToFract)) {
            n += sm[j++] * pow(-1, minIsTerm2 && minusTerm2);
        }
        n += bg[i] * pow(-1, !minIsTerm2 && minusTerm2);

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
    }

    if (transfer > 0 && !addToFract) {
        res.appendToInt(transfer);
    }

    return transfer;
}
