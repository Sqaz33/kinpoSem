#include "../include/BigRealNumber.h"
#include "testInstruments.h"
#include <math.h>

#include <string>
#include <QStringBuilder>
#include <QString>
#include <QtTest/QtTest>

#define MAX_LENGTH 1000

using std::string;
using namespace test_instruments;

class BigRealNumberTest : public QObject
{
    Q_OBJECT

private slots:
    // test BigRealNumber BigRealNumber::fromStdString(const string& numb)
    void fromStdString_tests_data();
    void fromStdString_tests();

    // test bool BigRealNumber::validateQString(const QString& numb)
    void validateQString_tests_data();
    void validateQString_tests();

    // test std::string BigRealNumber::toStdString(const BigRealNumber& other)
    void toStdString_tests_data();
    void toStdString_tests();

    // test BigRealNumber BigRealNumber::operator+(const BigRealNumber& other)
    void operatorAdd_tests_data();
    void operatorAdd_tests();

    // test BigRealNumber BigRealNumber::operator-(const BigRealNumber& other)
    void operatorSub_tests_data();
    void operatorSub_tests();

    // test BigRealNumber BigRealNumber::operator*(const BigRealNumber& other)  
    void operatorMul_tests_data();
    void operatorMul_tests();

    // test BigRealNumber BigRealNumber::operator/(const BigRealNumber& other)  
    void operatorDiv_tests_data();
    void operatorDiv_tests();

    // test BigRealNumber BigRealNumber::pow(const BigRealNumber& other)  
    void pow_tests_data();
    void pow_tests();

    // test BigRealNumber BigRealNumber::factorial() 
    void factorial_tests_data();
    void factorial_tests();

    // test bool BigRealNumber::operator==(const BigRealNumber& other)  
    void operator_eq_data();
    void operator_eq();

    
    // test bool BigRealNumber::operator>(const BigRealNumber& other) 
    void operator_more_data();
    void operator_more();
};

void BigRealNumberTest::fromStdString_tests_data() {
    QTest::addColumn<QString>("inputString");
    QTest::addColumn<QList<int>>("expectedIntPrt");
    QTest::addColumn<QList<int>>("expectedFractPrt");
    QTest::addColumn<int>("expectedIntPrtLen");
    QTest::addColumn<int>("expectedFractPrtLen");
    QTest::addColumn<bool>("expectedIsNegative");

    QTest::addRow("max_length") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH)
                              << genIntPrt(MAX_LENGTH)
                              << genFractPrt(MAX_LENGTH)
                              << MAX_LENGTH << MAX_LENGTH << true;

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

    QTest::addRow("max_length") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH);
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

    QTest::addRow("max_operands") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 2, 2, false);
    QTest::addRow("min_operands") << "1.0" << "1.0" << "2.0";
    
    QTest::addRow("second_operand_len_more") << "0.0" << "0.01" << "0.01";
    QTest::addRow("first_operand_len_more") << "0.01" << "0.0" << "0.01";


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
    QTest::addRow("max_operands") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                  << "0.0";
    QTest::addRow("min_operands") << "1.0" << "1.0" << "0.0";
    
    QTest::addRow("second_operand_len_more") << "0.0" << "0.01" << "-0.01";
    QTest::addRow("first_operand_len_more") << "0.01" << "0.0" << "0.01";


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

    QTest::addRow("simple_case_1") << "2.0" << "2.0" << "4.0";
    QTest::addRow("simple_case_2") << "0.1" << "0.1" << "0.01";

    QTest::addRow("max_length_int_res") << genQStrNumb_m1xp0x1((MAX_LENGTH-10)+1, 0, 1, 0, false)
                                        << genQStrNumb_m1xp0x1((MAX_LENGTH-991)+1, 0, 1, 0, false)
                                        << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false);
    QTest::addRow("max_length_fract_operand") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                              << "1.0" 
                                              << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false);

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
                                          << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false)  
                                          << genQStrNumb_m1xp0x1(0, MAX_LENGTH-1, 0, 1, false);

    QTest::addRow("max_length_int_res") << genQStrNumb_m1xp0x1(MAX_LENGTH-1, 0, 5, 0, false)
                                        << "0.5"
                                        << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false);

    
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

void BigRealNumberTest::pow_tests_data() {
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("p");
    QTest::addColumn<QString>("res");

    QTest::addRow("simple_case") << "10.0" << "10.0" << "10000000000.0";

    QTest::addRow("10_pow_max_length_int_res") << "10.0" << "999.0" 
                                               <<  QString("1") + QString("0").repeated(MAX_LENGTH-1) + QString(".0"); // 1...000.0
    QTest::addRow("0_1_pow_max_length_fract_res") << "0.1" << "2.0" 
                                                  << QString("0.") + QString("0").repeated(1) + QString("1"); // 0.000...1
}


void BigRealNumberTest::pow_tests() {
    QFETCH(QString, b);
    QFETCH(QString, p);
    QFETCH(QString, res);


    BigRealNumber r = BigRealNumber::fromStdString(b.toStdString())
                      .pow(BigRealNumber::fromStdString(p.toStdString()));
    qDebug() << b.left(5) << " ** " << p.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    QCOMPARE(QString::fromStdString(r.toStdString()), res);
}

void BigRealNumberTest::factorial_tests_data() {
    QTest::addColumn<QString>("f");
    QTest::addColumn<QString>("res");

    QTest::addRow("simple_case") << "5.0" << "120.0";
}


void BigRealNumberTest::factorial_tests() {
    QFETCH(QString, f);
    QFETCH(QString, res);

    BigRealNumber r = BigRealNumber::fromStdString(f.toStdString()).factorial();
    qDebug() << "fact(" << f.left(5) << ")" << " = " << QString::fromStdString(r.toStdString()).left(5);
    QCOMPARE(QString::fromStdString(r.toStdString()), res);
}



void BigRealNumberTest::operator_eq_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<bool>("res");

    QTest::addRow("simple_case_1") << "1.0" << "1.0" << true;
    QTest::addRow("simple_case_3") << "2.0" << "1.0" << false;

    
    QString buf = genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0);
    QTest::addRow("max_len_int_operands") << buf << buf << true;
    buf = genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1);
    QTest::addRow("max_len_fract_operands") << buf << buf << true; 

    QTest::addRow("neg_pos_operands") << "-1.0" << "1.0" << false;
}

void BigRealNumberTest::operator_eq() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             == BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " == " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}


void BigRealNumberTest::operator_more_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<bool>("res");

    QTest::addRow("simple_case_1") << "2.0" << "1.0" << true;
    QTest::addRow("simple_case_2") << "0.0" << "1.0" << false;

    
    QTest::addRow("max_int_operands_first_more") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                 << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                 << true;
        
    QTest::addRow("max_int_operands_second_more") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                  << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                  << false;

    QTest::addRow("max_fract_operands_first_more") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 2, 0, false) 
                                                   << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 0, false)
                                                   << true;

    QTest::addRow("max_fract_operands_second_more") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 0, false) 
                                                    << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 2, 0, false)
                                                    << false;

    QTest::addRow("neg_neg_operand_first_abs_more") << "-2.0" << "-1.0" << false;
    QTest::addRow("neg_neg_operand_second_abs_more") << "-1.0" << "-2.0" << true;
    QTest::addRow("pos_neg_operand_second_abs_more") << "1.0" << "-3.0" << true;
    QTest::addRow("neg_pos_operand_first_abs_more") << "-3.0" << "-2.0" << false;
}

void BigRealNumberTest::operator_more() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             > BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " > " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}

QTEST_MAIN(BigRealNumberTest)

#include "BigRealNumberTests.moc"
