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
        numb.append(1, (char) ('0' + (int) intPrt[i]));
    }
    numb.append(1, '.');
    for (int i = fractPrtLen - 1; i >= 0; i--) {
        numb.append(1, (char) ('0' + (int) fractPrt[i]));
    }

    return numb;
}

BigRealNumber& BigRealNumber::operator=(const BigRealNumber &other) {
    isNegative = other.isNegative;
    fractPrtLen = other.fractPrtLen;
    intPrtLen = other.intPrtLen;

    fractPrt = new short[1000];
    intPrt = new short[1000];

    for (int i = 0; i < fractPrtLen; i++) {
        fractPrt[i] = other.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        fractPrt[i] = other.fractPrt[i];
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

    BigRealNumber res;
    res.isNegative = isNegative;

    // сложение дробных частей
    short trans = addArraysToBRL(other, res, true, 0);
    // сложение целых частей
    addArraysToBRL(other, res, false, trans);

    return res;
}

BigRealNumber BigRealNumber::operator-(const BigRealNumber &other) const {
    // this - other
    // -this - other
    // -this - (-other)
    // this - (-other)

    if ((isNegative && other.isNegative) || (!(isNegative) && other.isNegative)) {
        return *this + other; // -this - other; this - (-other)
    } else if (isNegative && other.isNegative) {
        // -this - (-other)
        BigRealNumber res = other;
        res.isNegative = false;
        res = res - *this;
        return res;
    }

    BigRealNumber res;



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
        const BigRealNumber &other,
        BigRealNumber &res,
        bool addToFract,
        short transfer
) const {
    int len1;
    int len2;
    if (addToFract) {
        len1 = fractPrtLen;
        len2 = other.fractPrtLen;
    } else {
        len1 = intPrtLen;
        len2 = other.intPrtLen;
    }

    short *bg; // больший массив
    short *sm; // меньший массив
    if (len1 > len2) {
        bg = addToFract ? fractPrt : intPrt;
        sm = addToFract ? other.fractPrt : other.intPrt;
    } else {
        bg = addToFract ? other.fractPrt : other.intPrt;
        sm = addToFract ? fractPrt : intPrt;
    }

    if (addToFract) {
        len1 = max(fractPrtLen, other.fractPrtLen);
        len2 = min(fractPrtLen, other.fractPrtLen);
    } else {
        len1 = max(intPrtLen, other.intPrtLen);
        len2 = min(intPrtLen, other.intPrtLen);
    }



    for (int i = 0, j = 0; i < len1; i++) {
        //90.90; 1000.001 пример
        // 0001.100
        // 09  . 09

        short n = transfer;
        // при сложении целых частей, начало меньшего массива прикладывается
        // к началу большего
        // при сложении дробных частей, конец меньшего массива прикладывается к
        // концу большего
        if ((i < len2 && !addToFract) || (i >= len1 - len2 && addToFract)) {
            n += sm[j++];
        }
        n += bg[i];
        transfer = n > 9 || n < -9;
        n %= 10;
        if (addToFract) {
            if (!res.appendToFract(n)) {
                break;
            }
        } else {
            res.appendToInt(n);
        }
    }

    if (transfer && !addToFract) {
        res.appendToInt(transfer);
    }

    return transfer;
}

