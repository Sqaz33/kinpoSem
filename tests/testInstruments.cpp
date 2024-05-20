#include "testInstruments.h"

namespace test_instruments {
    QString genQStrNumb_m1xp0x1(int intLen, int fractLen, int first_int, int last_fract, bool neg) {
        QString res = QString::number(first_int) 
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
}