#include "../include/BigRealNumber.h"

#include <string>

#include <QtTest/QtTest>

using std::string;

Q_DECLARE_METATYPE(string);

class BigRealNumberTest : public QObject
{
    Q_OBJECT

private slots:
    void fromBRNToString_data();
    void fromBRNToString();
};

void BigRealNumberTest::fromBRNToString_data() {
    QTest::addColumn<string>("toBrn");
    QTest::addColumn<string>("fromBrn");

    string s1("5.0");
    string s2("5.0");
    QTest::addRow("OrdinaryTest") << s1 << s2;
}

void BigRealNumberTest::fromBRNToString() {
    qDebug() << "Fetching test data...";
    QFETCH(string, toBrn);
    QFETCH(string, fromBrn);

    BigRealNumber t = BigRealNumber::fromStdString(toBrn);

    // int i = toBrn + 1;
    QCOMPARE(t.toStdString(), fromBrn);
}

QTEST_MAIN(BigRealNumberTest)

#include "BigRealNumberTests.moc"