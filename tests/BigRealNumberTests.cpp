#include "../include/BigRealNumber.h"
#include "testInstruments.h"

#include <string>
#include <QStringBuilder>
#include <QString>
#include <QtTest/QtTest>

using std::string;
using namespace test_instruments;

Q_DECLARE_METATYPE(string);

class BigRealNumberTest : public QObject
{
    Q_OBJECT

private slots:
    // test BigRealNumber::fromStdString(const string& numb)
    void fromStdString_tests_data();
    void fromStdString_tests();

    // test BigRealNumber::validateQString(const QString& numb)
    void validateQString_tests_data();
    void validateQString_tests();

    // test BigRealNumber::toStdString()
    void toStdString_tests_data();
    void toStdString_tests();

    // test BigRealNumber::operator+()
    void operatorAdd_tests_data();
    void operatorAdd_tests();

    // test BigRealNumber::operator-()
    void operatorSub_tests_data();
    void operatorSub_tests();

    // test BigRealNumber::operator*()  
    void operatorMul_tests_data();
    void operatorMul_tests();

    // test BigRealNumber::operator/()  
    void operatorDiv_tests_data();
    void operatorDiv_tests();
};

void BigRealNumberTest::fromStdString_tests_data() {
    QTest::addColumn<QString>("inputString");
    QTest::addColumn<QList<int>>("expectedIntPrt");
    QTest::addColumn<QList<int>>("expectedFractPrt");
    QTest::addColumn<int>("expectedIntPrtLen");
    QTest::addColumn<int>("expectedFractPrtLen");
    QTest::addColumn<bool>("expectedIsNegative");

    QTest::addRow("max_length") << genQStrNumb_m1xp0x1(1000, 1000)
                              << genIntPrt(1000)
                              << genFractPrt(1000)
                              << 1000 << 1000 << true;

    QTest::addRow("min_length") << "0.0" << QList<int>{0} << QList<int>{0} << 0 << 0 << false;

    QTest::addRow("negative_number") << "-123.456"
                                     << QList<int>{3, 2, 1}
                                     << QList<int>{4, 5, 6}
                                     << 3 << 3 << true;

    QTest::addRow("positive_number") << "123.456"
                                     << QList<int>{3, 2, 1}
                                     << QList<int>{4, 5, 6}
                                     << 3 << 3 << false;
}

void BigRealNumberTest::fromStdString_tests() {
    QFETCH(QString, inputString);
    QFETCH(QList<int>, expectedIntPrt);
    QFETCH(QList<int>, expectedFractPrt);
    QFETCH(int, expectedIntPrtLen);
    QFETCH(int, expectedFractPrtLen);
    QFETCH(bool, expectedIsNegative);

    BigRealNumber result = BigRealNumber::fromStdString(inputString.toStdString());

    QCOMPARE(result.getIntPrtLen(), expectedIntPrtLen);
    QCOMPARE(result.getFractPrtLen(), expectedFractPrtLen);
    QCOMPARE(result.negative(), expectedIsNegative);

    for (int i = 0; i < expectedIntPrtLen; ++i) {
        QCOMPARE(result.getIntPrt()[i], expectedIntPrt[i]);
    }

    for (int i = 0; i < expectedFractPrtLen; ++i) {
        QCOMPARE(result.getFractPrt()[i], expectedFractPrt[i]);
    }
}

void BigRealNumberTest::validateQString_tests_data() {
    QTest::addColumn<QString>("inputString");
    QTest::addColumn<bool>("isValid");

    // Корректные строки
    QTest::addRow("positive_number") << "123.456" << true;
    QTest::addRow("negative_number") << "-123.456" << true;
    QTest::addRow("zero") << "0.0" << true;
    QTest::addRow("max_int_part") << QString("1").repeated(1000) + ".0" << true;
    QTest::addRow("max_fract_part") << "0." + QString("0").repeated(1000) << true;

    // Некорректные строки
    QTest::addRow("no_decimal_point") << "123456" << false;
    QTest::addRow("multiple_decimal_points") << "123.45.6" << false;
    QTest::addRow("invalid_character_in_integer_part") << "12a.456" << false;
    QTest::addRow("invalid_character_in_fractional_part") << "123.45b" << false;
    QTest::addRow("too_long_integer_part") << QString("1").repeated(1001) + ".0" << false;
    QTest::addRow("too_long_fractional_part") << "1." + QString("0").repeated(1001) << false;
    QTest::addRow("negative_with_invalid_character") << "-12a.456" << false;
    QTest::addRow("empty_string") << "" << false;
    QTest::addRow("only_decimal_point") << "." << false;
    QTest::addRow("only_minus") << "-" << false;
    QTest::addRow("minus_with_decimal_point") << "-." << false;
}

void BigRealNumberTest::validateQString_tests() {
    QFETCH(QString, inputString);
    QFETCH(bool, isValid);

    bool result = BigRealNumber::validateQString(inputString);
    qDebug() << inputString.left(5) << QString::number(isValid) << " --> "<< QString::number(result);
    QCOMPARE(result, isValid);
}

void BigRealNumberTest::toStdString_tests_data() {
    QTest::addColumn<QString>("inputString");

    QTest::addRow("max_length") << genQStrNumb_m1xp0x1(1000, 1000);
    QTest::addRow("min_length") << "0.0";
    QTest::addRow("negative_number") << "-123.456";
    QTest::addRow("positive_number") << "123.456";
}

void BigRealNumberTest::toStdString_tests() {
    QFETCH(QString, inputString);

    BigRealNumber brn = BigRealNumber::fromStdString(inputString.toStdString());
    QString resultString = QString::fromStdString(brn.toStdString());
    qDebug() << inputString.left(5) << " --> "<< resultString.left(5);
    QCOMPARE(resultString, inputString);
}

void BigRealNumberTest::operatorAdd_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");

    QTest::addRow("max_operands") << genQStrNumb_m1xp0x1(1000, 1000, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(1000, 1000, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(1000, 1000, 2, 2, false);
    QTest::addRow("min_operands") << "1.0" << "1.0" << "2.0";

    QTest::addRow("pos_neg_operands_pos_res") << "2.0" << "-1.0" << "1.0";
    QTest::addRow("neg_pos_operands_pos_res") << "-1.0" << "2.0" << "1.0";
    QTest::addRow("neg_pos_operands_neg_res") << "-2.0" << "1.0" << "-1.0";
    QTest::addRow("neg_neg_operands_neg_res") << "-1.0" << "-1.0" << "-2.0";
    QTest::addRow("null_res") << "1.0" << "-1.0" << "0.0";
}

void BigRealNumberTest::operatorAdd_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);

    BigRealNumber r = BigRealNumber::fromStdString(a.toStdString())
                      + BigRealNumber::fromStdString(b.toStdString());
    qDebug() << a.left(5) << " + " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    QCOMPARE(r.toStdString(), res.toStdString());
}

void BigRealNumberTest::operatorSub_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");

    // test length operands
    QTest::addRow("max_operands") << genQStrNumb_m1xp0x1(1000, 1000, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(1000, 1000, 1, 1, false)
                                  << "0.0";
    QTest::addRow("min_operands") << "1.0" << "1.0" << "0.0";

    // test 
    QTest::addRow("pos_neg_operands_pos_res") << "2.0" << "-1.0" << "3.0";
    QTest::addRow("neg_pos_operands_neg_res") << "-1.0" << "2.0" << "-3.0";
    QTest::addRow("neg_pos_operands_neg_res") << "-2.0" << "1.0" << "-3.0";
    QTest::addRow("neg_neg_operands_pow_res") << "-1.0" << "-2.0" << "1.0";
    QTest::addRow("pos_pos_operand_null_res") << "1.0" << "1.0" << "0.0";
}

void BigRealNumberTest::operatorSub_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);

    BigRealNumber r = BigRealNumber::fromStdString(a.toStdString())
                      - BigRealNumber::fromStdString(b.toStdString());
    qDebug() << a.left(5) << " - " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    QCOMPARE(r.toStdString(), res.toStdString());
}   

void BigRealNumberTest::operatorMul_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");

    QTest::addRow("max_length_int_res") << genQStrNumb_m1xp0x1(990+1, 0, 1, 0, false)
                                        << genQStrNumb_m1xp0x1(9+1, 0, 1, 0, false)
                                        << genQStrNumb_m1xp0x1(1000, 0, 1, 0, false);
    QTest::addRow("max_length_fract_operand") << genQStrNumb_m1xp0x1(0, 1000, 0, 1, false) 
                                              << "1.0" 
                                              << genQStrNumb_m1xp0x1(0, 1000, 0, 1, false);

    QTest::addRow("null_pos_operands_null_res") << "0.0" << "1.0" << "0.0";
    QTest::addRow("pos_null_operands_null_res") << "1.0" << "0.0" << "0.0";

    QTest::addRow("pos_neg_operands_neg_res") << "1.0" << "-1.0" << "-1.0";
    QTest::addRow("neg_pos_operands_neg_res") << "-1.0" << "1.0" << "-1.0";
    QTest::addRow("neg_neg_operands_pos_res") << "-1.0" << "-1.0" << "1.0";
}

void BigRealNumberTest::operatorMul_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);

    BigRealNumber r = BigRealNumber::fromStdString(a.toStdString())
                      * BigRealNumber::fromStdString(b.toStdString());
    qDebug() << a.left(5) << " * " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    QCOMPARE(r.toStdString(), res.toStdString());
}

void BigRealNumberTest::operatorDiv_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");


    QTest::addRow("max_length_fract_res") << "1.0" 
                                          << genQStrNumb_m1xp0x1(1000, 0, 1, 0, false)  
                                          << genQStrNumb_m1xp0x1(0, 999, 0, 1, false);

    QTest::addRow("max_length_int_res") << genQStrNumb_m1xp0x1(999, 0, 5, 0, false)
                                        << "0.5"
                                        << genQStrNumb_m1xp0x1(1000, 0, 1, 0, false);

    QTest::addRow("cyclic_fraction_res") << "1.0" << "3.0" 
                                         << QString('0') + QString('.') + QString("3").repeated(1000);

    QTest::addRow("null_pos_operands_null_res") << "0.0" << "1.0" << "0.0";

    QTest::addRow("pos_neg_operands_neg_res") << "1.0" << "-1.0" << "-1.0";
    QTest::addRow("neg_pos_operands_neg_res") << "-1.0" << "1.0" << "-1.0";
    QTest::addRow("neg_neg_operands_pos_res") << "-1.0" << "-1.0" << "1.0";
}

void BigRealNumberTest::operatorDiv_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);

    BigRealNumber r = BigRealNumber::fromStdString(a.toStdString())
                      / BigRealNumber::fromStdString(b.toStdString());
    qDebug() << a.left(5) << " / " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    QCOMPARE(r.toStdString(), res.toStdString());
}


QTEST_MAIN(BigRealNumberTest)

#include "BigRealNumberTests.moc"
