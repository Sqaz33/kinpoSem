#include "BigRealNumber.h"

// скопировать значения из объекта p в данный объект
BigRealNumber::BigRealNumber(const BigRealNumber& p) {
    // скопировать поля исходного объекта в новый объект
    isNegative = p.isNegative;
    fractPrtLen = p.fractPrtLen;
    intPrtLen = p.intPrtLen;

    this->fractPrt = new short[1000] {};
    this->intPrt = new short[1000] {};

    // для каждого числа из дробной части исходного объекта
    for (int i = 0; i < fractPrtLen; i++) {
        // внести в дробную часть нового объекта
        this->fractPrt[i] = p.fractPrt[i];
    }
    // для каждого числа из целой части исходного объекта
    for (int i = 0; i < intPrtLen; i++) {
        // внести в целую часть нового объекта
        this->intPrt[i] = p.intPrt[i];
    }
}

// получить из строки целую и дробную части, представленные массивами своих цифр
BigRealNumber::BigRealNumber(const string &numb) {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
    // если строка имеет знак "-"
    isNegative = numb.at(0) == '-'; // то число отрицательное

    // получить из строки индекс знака, разделяющего части
    int point = (int) numb.find('.');

    // длинна целой части = индек разделяющего знака
    // если число число отрицательно, длинна целой части -= 1
    intPrtLen = point - isNegative;
    
    // длинна дробной части = длинна строки - длинна целой части - 1
    // если число число отрицательно, длинна дробной части -= 1
    fractPrtLen = numb.length() - intPrtLen - 1 - isNegative;

    // записать в массив целой части цифры из целой части строки в обратном порядке
    int j = isNegative ? 1 : 0;
    for (int i = intPrtLen - 1; i >= 0; i--, j++) {
        intPrt[i] = (short)(numb.at(j) - '0');
    }
    j++;
    // записать в массив дробной части цифры из дробной части строки в прямом порядке
    for (int i = 0; i < fractPrtLen; i++, j++) {
        fractPrt[i] = (short)(numb.at(j) - '0');
    }
    // убрать из массивом целой и дробной частей незначащие разряды
    removeInsignDigits();
}

// получить из числа целую часть, представленную массивом своих цифр
BigRealNumber::BigRealNumber(int n) {
    intPrt = new short[1000] {};
    fractPrt = new short[1000] {};
    fractPrtLen = 0;
    intPrtLen = 0;
    isNegative = n < 0;
    
    // пока число > 0
    while (n > 0) {
        // записать в массив целой части остаток от деления числа на 10
        intPrt[intPrtLen++] = (short)n % 10;
        // поделить число на 10 нацело
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

// получить из дробного и целого массивов цифр число, в виде строки
string BigRealNumber::toString() const {
    string numb;
    // если число отрицательно
    if (isNegative) {
         // добавить знак "-"
        numb.append(1, '-');
    }
    // для каждого значения из целой части, начиная с последнего
    for (int i = intPrtLen - 1; i >= 0; i--) {
        // добавить значение в строку
        numb.append(1, (char)('0' + (int)intPrt[i]));
    }
    // если длинна целой части = 0
    if (!intPrtLen) {
        // добавить в строку 0
        numb.append(1, '0');
    }
    // добавить в строку знак, разделяющий целую и дробную части
    numb.append(1, '.');
    // для каждого значение из дробной части 
    for (int i = 0; i < fractPrtLen; i++) {
        // добавить значение в строку
        numb.append(1, (char)('0' + (int)fractPrt[i]));
    }
    // если длинна дробной части = 0
    if (!fractPrtLen) {
        // добавить в строку 0
        numb.append(1, '0');
    }
    return numb;
}

//-----------------------------------------------------
BigRealNumber &BigRealNumber::operator=(const BigRealNumber &other) {
    isNegative = other.isNegative;
    fractPrtLen = other.fractPrtLen;
    intPrtLen = other.intPrtLen;

    //if (intPrt != nullptr) {
    //    delete intPrt;
    //}
    intPrt = new short[1000] {};
    //if (fractPrt != nullptr) {
    //    delete fractPrt;
    //}
    fractPrt = new short[1000] {};

    for (int i = 0; i < fractPrtLen; i++) {
        this->fractPrt[i] = other.fractPrt[i];
    }
    for (int i = 0; i < intPrtLen; i++) {
        this->intPrt[i] = other.intPrt[i];
    }

    return *this;
}

// сложить данное слагаемое с другми
BigRealNumber BigRealNumber::operator+(const BigRealNumber &other) const {
    // this + other
    // -this + other
    // this + (-other)
    // -this + (-other)

    // если данное слагаемое положительно, а другое отрицательно
    if (!(isNegative) && other.isNegative) { // this + (-other)
        // результат = вычесть из данного слагаемого другое
        return *this - other;
    } else if (isNegative && !other.isNegative) { // -this + other если данное слагаемое отрицательно, а другое положительно
        // результат = вычесть из другого слагаемого данное
        return other - *this;
    }

    // this + other
    // -this + (-other)
    // знак результата = знаку первого слагаемого
    BigRealNumber res{};
    res.isNegative = isNegative;

    // дробная часть результата = сложить дробные части слагаемых с сохранением переноса
    short trans = attachArrays(*this, other,
                                 res, true,
                                 false, 0);
    // целая часть результата = сложить целые части слагаемых + перенос
    attachArrays(*this, other,
                   res, false,
                   false, trans);

    // удалить незначащие разряды в результате
    res.removeInsignDigits();
    return res;
}

BigRealNumber BigRealNumber::operator+(int n) const {
    return *this + BigRealNumber(n);
}

// вычесть из данного числа другое
BigRealNumber BigRealNumber::operator-(const BigRealNumber &other) const {
    // this - other
    // -this - other
    // -this - (-other)
    // this - (-other)

    BigRealNumber res{};
    // если данное число отрицательно и другое число отрицательно
    // или данной число не отрицательно и другое число отрицательно
    if ((isNegative && other.isNegative) || (!(isNegative) && other.isNegative)) {
        // -this - other; 
        // this - (-other) = this + other
        // резлуьтат = сложить данное число с другим, без учетов знаков
        BigRealNumber oth = other;
        BigRealNumber ths = *this;
        oth.isNegative = false;
        ths.isNegative = false;
        res = oth + ths;
        // знак результата = знак данного числа
        res.isNegative = isNegative;
        return  res;
    } else if (isNegative && other.isNegative) {
        // если данное число отрицательно и другое число отрицательно
        // -this - (-other) = other - this
        res = other;
        res.isNegative = false;
        // сменить знак другого число на +
        // результат = вычесть из другого числа данное
        res = res - *this;
        return res;
    }

    // this - other
    // если данное число больше другого
    if (*this >= other) {
        // результат = вычесть из данного числа другое

        // дробная часть результата = вычесть из дробной части данного числа дробную часть другого
        // сохранить перенос
        short trans = attachArrays(*this, other,
                                    res, true,
                                    true, 0);
        // целая часть результата = вычесть из целой части данного числа целую часть другого + перенос
        attachArrays(*this, other,
                     res, false,
                     true, trans);
        // убрать незначащие разряды из результата
        res.removeInsignDigits();
        return res;
    } else {
        // иначе, результат = вычесть из другого числа данное
        res = other - *this;
        // знак результата = "-"
        res.isNegative = true;
        return res;
    }
}

BigRealNumber BigRealNumber::operator-(int n) const {
    return *this - BigRealNumber(n);
}

// перемножить числа
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
    //delete &ths, & oth;
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
    
    //delete& ths, & oth;
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

bool BigRealNumber::appendToFract(short number, int ind) {
    if (fractPrtLen + 1 >= 1000  || ind >= 1000) {
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

//----------------------------------------------------------------
int getFirstNotZero(short* arr, int start, int stop, bool backward) {
    for (int i = start; i != stop; i += pow(-1, backward)) {
        if (arr[i]) {
            return i;
        }
    }
    return -1;
}