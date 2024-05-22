#ifndef TEST_INSTR
#define TEST_INSTR

#include <QString>
#include <QStringBuilder>
#include <QList>

namespace test_instruments {
    QString genQStrNumb_m1xp0x1(
        int intLen, int fractLen, int firstInt = 1, 
        int lastFract = 1, bool neg = true
    );
    QList<int> genIntPrt(int length);
    QList<int> genFractPrt(int length);
}

#endif
