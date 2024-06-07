#include "../include/BigRealNumber.h"
//TODO: for tests
BigRealNumber::BigRealNumber(std::vector<short> &intP, std::vector<short> &fractP, bool isNeg) {
    intPrt = new short[MAX_LENGTH];
    fractPrt = new short[MAX_LENGTH];
    intPrtLen = intP.size();
    fractPrtLen = fractP.size();
    isNegative = isNeg;
    for (int i = 0; i < intPrtLen; i++) {
        intPrt[i] = intP.at(i);
    }
    for (int i = 0; i < fractPrtLen; i++) {
        fractPrt[i] = fractP.at(i);
    }
}

BigRealNumber::BigRealNumber(const BigRealNumber& p) {
    isNegative = p.isNegative;
    fractPrtLen = p.fractPrtLen;
    intPrtLen = p.intPrtLen;

    this->intPrt = new short[MAX_LENGTH] {};
    this->fractPrt = new short[MAX_LENGTH] {};

    for (int i = 0; i < fractPrtLen; i++) {
        this->fractPrt[i] = p.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        this->intPrt[i] = p.intPrt[i];
    }
}

BigRealNumber BigRealNumber::fromStdString(const string& numb) {
    if (!validateStdString(numb)) {
        QRegExp rx ("-{0,1}\\d+\\.\\d+");
        if (!rx.exactMatch(QString::fromStdString(numb))) {
            throw ActionBuildError(INVALID_OPERAND_FORMAT);
        }
    }

    BigRealNumber n;
    n.isNegative = numb.at(0) == '-';

    // Получить индекс разделителя
    int point = (int)numb.find('.');
    // Получить длину целой части
    n.intPrtLen = point - n.isNegative;

    // Получить длину дробной части
    n.fractPrtLen = numb.length() - n.intPrtLen - 1 - n.isNegative;

    if (n.fractPrtLen > MAX_LENGTH || n.intPrtLen > MAX_LENGTH) {
        throw ActionBuildError(INVALID_LENGTH);
    }

    n.intPrt = new short[MAX_LENGTH] {};
    n.fractPrt = new short[MAX_LENGTH] {};
    // Записать целую часть в обратном порядке
    int j = n.isNegative ? 1 : 0;
    for (int i = n.intPrtLen - 1; i >= 0; i--, j++) {
        n.intPrt[i] = (short)(numb.at(j) - '0');
    }
    j++;

    // Записать дробную часть
    for (int i = 0; i < n.fractPrtLen; i++, j++) {
        n.fractPrt[i] = (short)(numb.at(j) - '0');
    }
    // Удалить незначащие разряды
    n.removeInsignDigits();
    return n;
}

bool BigRealNumber::validateStdString(const string& numb) {
    QString n = QString::fromStdString(numb);
    return validateQString(n);
}

bool BigRealNumber::validateQString(const QString& numb) {
    QRegExp rx("-{0,1}\\d{1,1000}\\.\\d{1,1000}");
    return rx.exactMatch(numb);
}

bool BigRealNumber::negative() const {
    return isNegative;
}

BigRealNumber::BigRealNumber(int n) {
    intPrt = new short[MAX_LENGTH] {};
    fractPrt = new short[MAX_LENGTH] {};
    intPrtLen = 0;
    fractPrtLen = 0;
    isNegative = n < 0;
    setVal(n);
}

BigRealNumber::BigRealNumber() {
    intPrt = new short[MAX_LENGTH] {};
    fractPrt = new short[MAX_LENGTH] {};
    intPrtLen = 0;
    fractPrtLen = 0;
    isNegative = false;
}

BigRealNumber::~BigRealNumber() {
    delete fractPrt;
    delete intPrt;
}

int BigRealNumber::getIntPrtLen() const {
    return intPrtLen;
}
int BigRealNumber::getFractPrtLen() const {
    return fractPrtLen;
}

string BigRealNumber::toStdString() const {
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

BigRealNumber& BigRealNumber::operator=(bool bl) {
    this->setVal(bl ? 1 : 0);
    return *this;
}

BigRealNumber BigRealNumber::operator+(const BigRealNumber& other) const {
    BigRealNumber res;
    add(other, res); 
    return res;
}

BigRealNumber BigRealNumber::operator+(int n) const {
    return *this + BigRealNumber(n);
}


BigRealNumber BigRealNumber::operator-(const BigRealNumber& other) const {
    BigRealNumber res;
    sub(other, res);
    return res;
}

BigRealNumber BigRealNumber::operator-(int n) const {
    return *this - BigRealNumber(n);
}

BigRealNumber BigRealNumber::operator*(const BigRealNumber& other) const {
    BigRealNumber mult = *this;
    BigRealNumber fac = other;
    fac.isNegative = false;
    mult.isNegative = false;

    BigRealNumber res;
    mult.mul(fac, res);
    res.isNegative = isNegative != other.isNegative;

    return res;
}

BigRealNumber BigRealNumber::operator*(int n) const {
    return *this * BigRealNumber(n);
}

BigRealNumber BigRealNumber::operator/(const BigRealNumber& other) const {
    if (other == 0) {
        throw ActionPerformError(DIVISION_BY_ZERO);
    }
    BigRealNumber ths = *this;
    BigRealNumber oth = other;
    ths.isNegative = false;
    oth.isNegative = false;

    BigRealNumber res;
    ths.div(oth, res);
    res.isNegative = isNegative != other.isNegative;
    return res;
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

bool BigRealNumber::operator==(int other) const {
    return *this == BigRealNumber(other);
}

bool BigRealNumber::operator!=(const BigRealNumber& other) const {
    return !(*this == other);
}

bool BigRealNumber::operator!=(int other) const {
    return !(*this == BigRealNumber(other));
}

bool BigRealNumber::operator<(const BigRealNumber& other) const {
    return *this != other && !(*this > other);
}

bool BigRealNumber::operator>(const BigRealNumber& other) const {
    if (isNegative && !other.isNegative)  {
        return false;
    } else if (!isNegative && other.isNegative) {
        return true;
    }

    // Если целая часть больше
    if (intPrtLen > other.intPrtLen) {
        return true && !isNegative;
    } else if (intPrtLen < other.intPrtLen) {
        return false && !isNegative;
    }
    // Сравнивать целые части начиная со старших разрядов
    for (int i =  intPrtLen - 1; i >= 0; i--) {
        if (intPrt[i] > other.intPrt[i]) {
            return true && !isNegative;
        } else if (intPrt[i] < other.intPrt[i]) {
            return false || isNegative;
        }
    }
    // Сравнить дробные части
    for (int i = 0; i < max(fractPrtLen, other.fractPrtLen); i++) {
        if (fractPrt[i] > other.fractPrt[i]) {
            return true && !isNegative;
        }
        else if (fractPrt[i] < other.fractPrt[i]) {
            return false || isNegative;
        }
    }
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

BigRealNumber BigRealNumber::pow(BigRealNumber pw) const{
    if (pw.fractPrtLen) {
        throw ActionPerformError(
            POW_WITH_FRACTIONAL_PART
        );
    }
    if (pw < 0) {
        throw ActionPerformError(
           NEGATIVE_POS
        );
    }
    BigRealNumber res(1);
    if (pw == 0) {
        return res;
    }

    while (pw > 0) {
        res = res * *this;
        pw = pw - 1;
    }
    return res;
}

BigRealNumber BigRealNumber::factorial() const{
    bool isError = false;
    if (fractPrtLen) {
        throw ActionPerformError(
            POW_WITH_FRACTIONAL_PART
        );
    }
    if (*this < 0) {
        throw ActionPerformError(
            OPERAND_LESS_ZERO_POW_FACT
        );
    }

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


void BigRealNumber::add(
        const BigRealNumber& term2,
        BigRealNumber& res
) const {
    // Если term1 + (-term2)
    if (!(isNegative) && term2.isNegative) {
        // res = term1 - term2
        BigRealNumber buf = term2;
        buf.isNegative = false;
        this->sub(buf, res);
        return;
    // Если -term1 + term2
    } else if (isNegative && !term2.isNegative) {
        // res = term2 - term1
        BigRealNumber buf = *this;
        buf.isNegative = false;
        term2.sub(buf, res);
        return;
    } 
    // На случай подобного: term1.add(term2, term1)
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
    const BigRealNumber& subtractor,
    BigRealNumber& res
) const {
   // term1 - term2
   // term1 - (-term2)
   // -term1 - term2
   // -term1 - (-term2) 

    // Если -term1 - term2 или term1 - (-term2a) 
    if ((isNegative && !subtractor.isNegative) || (!(isNegative) && subtractor.isNegative)) {
        BigRealNumber buf = subtractor;
        buf.isNegative = isNegative;
        this->add(buf, res);
        res.isNegative = isNegative;
        return;
    // Если -term1 - (-term2)
    } else if (isNegative && subtractor.isNegative) {
        // res = term2 - term1
        BigRealNumber ths = *this;
        BigRealNumber sb = subtractor;
        ths.isNegative = false;
        sb.isNegative = false;
        sb.sub(ths, res);
        return;
    }
    // Иначе вычислить term1 - term2

    if (*this >= subtractor) {
        BigRealNumber *rs = this == &res ? new BigRealNumber() : &res;
        short trans = attachArrays(*this, subtractor,
                                    *rs, true,
                                    true, 0);
        attachArrays(*this, subtractor,
                      *rs, false,
                      true, trans);
        rs->removeInsignDigits();
        if (this == &res) {
            res = *rs;
        }
    } else {
        // res = -(term2 - term1)
        subtractor.sub(*this, res);
        res.isNegative = true;
    }
}

void BigRealNumber::mul(
    const BigRealNumber& fac,
    BigRealNumber &res
) const {

    // Умножаем на 1 цифру из числа
    if (fac.intPrtLen == 1 && !fac.fractPrtLen) {
        short ref = 0; // перенос
        short f = fac.intPrt[0]; // множитель
        // Умножить начиная с младших разрядов столбиком
        // Дробную часть
        for (int i = fractPrtLen - 1; i >= 0; i--) {
            short n = fractPrt[i] * f + ref;
            ref = n / 10;
            n %= 10;
            res.appendToFract(n, i);
        }  
        // Целую часть
        for (int i = 0; i < intPrtLen; i++) {
            short n = intPrt[i] * f + ref;
            ref = n / 10;
            n %= 10;
            res.appendToInt(n);
        }
        // Если остался перенос
        if (ref) {
            res.appendToInt(ref);
        }
        return;
    }
    
    // Умножить начиная с младших разрядов столбиком
    BigRealNumber buf1;
    BigRealNumber buf2;
    // Дробную часть
    for (int i = fac.fractPrtLen - 1; i >= 0; i--) {
        buf2.setVal(0);
        buf1.setVal(fac.fractPrt[i]);
        // Умножить множиемое на i-ый разряд множителя
        mul(buf1, buf2);
        // Сдвинуть результат предыдущей операции вправо
        buf2.shiftNumber(i + 1, true);
        // Прибавить к ответу
        res.add(buf2, res);
    }
    // Целую часть
    for (int i = 0; i < fac.intPrtLen; i++) {
        buf2.setVal(0);
        buf1.setVal(fac.intPrt[i]);
        mul(buf1, buf2);
        // Сдвинуть ... влево
        buf2.shiftNumber(i, false);
        res.add(buf2, res);
    }
}

void BigRealNumber::div(
    const BigRealNumber& diver,
    BigRealNumber& res
) const {
    BigRealNumber dcp = diver; 
    BigRealNumber ths = *this;
    ths.shiftNumber(dcp.fractPrtLen, false);
    dcp.shiftNumber(dcp.fractPrtLen, false);
    ths.removeInsignDigits();
    dcp.removeInsignDigits();

    BigRealNumber q; // Остаток
    BigRealNumber r; // Целая часть
    BigRealNumber divid; // Буфер для столбика
    int i = ths.intPrtLen - 1; // Начальный индекс для целой части делимого
    int j = 0; // Начальный индекс для дробной части делимого
    int fp = -1; // Индек для внесения в дробную часть результата
    bool toF = false; // Флаг внесения в дробную часть результа     
    // Пока не выбрана целая или дробная часть делимого, или пока имеется остаток
    while ((i >= 0 || j < fractPrtLen || q != 0) && res.fractPrtLen < MAX_LENGTH) {
        // буфер = остаток //
        divid = q;
        q.setVal(0);
        r.setVal(0);
        while (divid < dcp) {
            divid.shiftNumber(1, false);
    
            // Взять разряд из целой части 
            if (i >= 0) {
                divid.intPrt[0] = ths.intPrt[i--];
            } else if (j < fractPrtLen) {
                divid.intPrt[0] = ths.fractPrt[j++];
                toF = true;
            } else {
                toF = true;
            } 
            divid.removeInsignDigits();

            if (toF) {
                fp++;
            } else {
                res.shiftNumber(1, false);
            }

            if (divid == 0) {
                break;
            }
        }
        // поделить с остатком
        divid.divRemaind(dcp, r, q);
        if (toF) {
            res.appendToFract(r.intPrt[0], fp);
        } else {
            res.intPrt[0] = r.intPrt[0];
        }
    }
    res.removeInsignDigits();
}

void BigRealNumber::divRemaind(
    const BigRealNumber& diver,
    BigRealNumber& R,
    BigRealNumber& Q
) const {
    BigRealNumber s = *this;
    BigRealNumber one(1);
    BigRealNumber d = diver;
    while (s >= diver) {
        s.sub(diver, s);
        R.add(one, R);
    }
    Q = s;
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
        // Начинать с младших разрядов.
        start = max(term1.fractPrtLen, term2.fractPrtLen) - 1;
        start = max(0, start);
        stop = 0;
        diff = -1;
        t1 = term1.fractPrt;
        t2 = term2.fractPrt;
    } else {
        // Начинать с младших разрядов
        start = 0;
        stop = max(term1.intPrtLen, term2.intPrtLen) - 1;
        stop = max(0, stop);
        diff = 1;
        t1 = term1.intPrt;
        t2 = term2.intPrt;
    }

    for (int i = start; ; i += diff) {
        short n = transfer;
        n += t1[i] + t2[i] * std::pow(-1, minusTerm2);
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

void BigRealNumber::appendToInt(short number) {
    if (intPrtLen + 1 > MAX_LENGTH) {
        throw ActionPerformError(INTEGER_PART_OVERFLOW);
    }
    intPrt[intPrtLen++] = number;
}

bool BigRealNumber::appendToFract(short number, int ind) {
    if (ind >= MAX_LENGTH) {
        return false;
    }
    fractPrt[ind] = number;
    fractPrtLen = max(ind+1, fractPrtLen);
    return true;
}


void BigRealNumber::removeInsignDigits() {
    int signDigit = getFirstNotZero(intPrt, max(0, intPrtLen-1), -1, true);
    intPrtLen = signDigit + 1;
    signDigit = getFirstNotZero(fractPrt, max(0, fractPrtLen-1), -1, true);
    fractPrtLen = signDigit + 1;
}

void BigRealNumber::shiftNumber(int shift, bool toRight) {
    while (shift) {
        // Перенос младшего разряда из одного массива в другой 
        short buf = toRight ? intPrt[0] : fractPrt[0];
        if (intPrtLen || !toRight) {
            if (!toRight) {
                if (intPrtLen + 1 > MAX_LENGTH) {
                    throw ActionPerformError(INTEGER_PART_OVERFLOW);
                }
                intPrtLen++;
            }
            // сдвинуть целую часть 
            arrShift(intPrt, intPrtLen, 1, !toRight, 0);
            if (toRight && intPrtLen) {
                intPrtLen--;
            }
        }
        if (fractPrt || toRight) {
            if (toRight) {
                fractPrtLen++;
            }
            // Сдвинуть дробную часть
            arrShift(fractPrt, fractPrtLen, 1, toRight, 0);
            if (!toRight && fractPrtLen) {
                fractPrtLen--;
            }
        }
        // Подставить значение из буфера на место пустого разряда
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
    for (int i = start; i != stop; i += std::pow(-1, backward)) {
        if (arr[i]) {
            return i;
        }
    }
    return -1;
}
