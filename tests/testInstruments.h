#include <QString>
#include <QStringBuilder>
#include <QList>

namespace test_instruments {
    QString genQStrNumb_m1xp0x1(
        int intLen, int fractLen, int first_int = 1, 
        int last_fract = 1, bool neg = true
    );
    QList<int> genIntPrt(int length);
    QList<int> genFractPrt(int length);
}
