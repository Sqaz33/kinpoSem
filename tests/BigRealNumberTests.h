#ifndef BRN_TESTS
#define BRN_TESTS

#include "../include/BigRealNumber.h"
#include "../include/ActionError.h"
#include "testInstruments.h"

#include <string>
#include <optional>

#include <QStringBuilder>
#include <QString>
#include <QtTest/QtTest>

#define MAX_LENGTH 1000

using std::string;
using namespace test_instruments;

Q_DECLARE_METATYPE(std::optional<ActionBuildError>);
Q_DECLARE_METATYPE(std::vector<short>);
Q_DECLARE_METATYPE(std::optional<ActionPerformError>);



// tests for
//  BigRealNumber BigRealNumber::fromStdString(const string& numb)
//  bool BigRealNumber::validateQString(const QString& numb)
//  std::string BigRealNumber::toStdString(const BigRealNumber& other)
//  BigRealNumber BigRealNumber::operator+(const BigRealNumber& other)
//  BigRealNumber BigRealNumber::operator-(const BigRealNumber& other)
//  BigRealNumber BigRealNumber::operator*(const BigRealNumber& other)  
//  BigRealNumber BigRealNumber::operator/(const BigRealNumber& other)  
//  BigRealNumber BigRealNumber::pow(const BigRealNumber& other)  
//  BigRealNumber BigRealNumber::factorial() 
//  bool BigRealNumber::operator==(const BigRealNumber& other)  
//  bool BigRealNumber::operator>(const BigRealNumber& other)
class BigRealNumberTest : public QObject {
    Q_OBJECT
private slots:
    // // test BigRealNumber BigRealNumber::fromStdString(const string& numb)
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
    void operatorEq_data();
    void operatorEq();

    
    // test bool BigRealNumber::operator>(const BigRealNumber& other) 
    void operatorMore_data();
    void operatorMore();
};

#endif