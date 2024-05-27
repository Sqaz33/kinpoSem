#include "testInstruments.h"

namespace test_instruments {
    QString genQStrNumb_m1xp0x1(int intLen, int fractLen, int firstInt, int last_fract, bool neg) {
        QString res = QString::number(firstInt) 
                      % QString('0').repeated(intLen-1) 
                      % QString('.')
                      % QString('0').repeated(fractLen-1)
                      % QString::number(last_fract);
        return neg ? QString('-') + res : res;
    }

    QList<int> genIntPrt(int length) {
        QList<int> intPrt;
        for (int i = 0; i < length - 1; ++i) {
            intPrt.append(0);  // Заполняем цифрами от 0 до 9 циклически
        }
        intPrt.append(1);
        return intPrt;
    }

    QList<int> genFractPrt(int length) {
        QList<int> fractPrt;
        for (int i = 0; i < length - 1; ++i) {
            fractPrt.append(0);  // Заполняем цифрами от 0 до 9 циклически
        }
        fractPrt.append(1);
        return fractPrt;
    }

    std::vector<short> getVector(int length, short fillVal, bool isFract, short minDigit) {
        std::vector<short> vec;
        for (int i = 0; i < length; i++) {
            vec.push_back(fillVal);
        }
        if (isFract) {
            vec[length - 1] = minDigit;
        } else {
            vec[0] = minDigit;
            std::reverse(vec.begin(), vec.end());
        }
        return vec;
    }
}