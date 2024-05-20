#include <QtTest/QtTest>

class MyTestClass : public QObject
{
    Q_OBJECT

private slots:
    void test_case1();
    void test_case2();
};

void MyTestClass::test_case1()
{
    QVERIFY(true);  // Простой тест, который всегда проходит
}

void MyTestClass::test_case2()
{
    QCOMPARE(1 + 1, 2);  // Тест, который проверяет равенство
}

QTEST_MAIN(MyTestClass)
#include "BigRealNumberTests.moc"