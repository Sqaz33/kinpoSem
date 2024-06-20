#include "BigRealNumberTests.h"

void BigRealNumberTest::fromStdString_tests_data() {
    QTest::addColumn<QString>("inputString");
    QTest::addColumn<QList<int>>("expectedIntPrt");
    QTest::addColumn<QList<int>>("expectedFractPrt");
    QTest::addColumn<int>("expectedIntPrtLen");
    QTest::addColumn<int>("expectedFractPrtLen");
    QTest::addColumn<bool>("expectedIsNegative");
    QTest::addColumn<std::optional<ActionBuildError>>("error");


    QTest::addRow("simple_case") << "1.1" << QList<int>{1} << QList<int>{1} << 1 << 1 << false << std::optional<ActionBuildError>{};

    QTest::addRow("max_len") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH)
                              << genIntPrt(MAX_LENGTH)
                              << genFractPrt(MAX_LENGTH)
                              << MAX_LENGTH << MAX_LENGTH << true << std::optional<ActionBuildError>{};

    QTest::addRow("min_len") << "0.0" << QList<int>{0} << QList<int>{0} << 0 << 0 << false << std::optional<ActionBuildError>{};

    QTest::addRow("negative_number") << "-123.456"
                                     << QList<int>{3, 2, 1}
                                     << QList<int>{4, 5, 6}
                                     << 3 << 3 << true << std::optional<ActionBuildError>{};

    QTest::addRow("positive_number") << "123.456"
                                     << QList<int>{3, 2, 1}
                                     << QList<int>{4, 5, 6}
                                     << 3 << 3 << false << std::optional<ActionBuildError>{};

    QTest::addRow("maximum_insignificant_digits_int_prt") << QString("0").repeated(MAX_LENGTH - 1) + "1.1"
                                                          << QList<int>{1} << QList<int>{1}
                                                          << 1 << 1 << false << std::optional<ActionBuildError>{};

    QTest::addRow("maximum_insignificant_digits_fract_prt") << "1.1" + QString("0").repeated(MAX_LENGTH - 1)
                                                            << QList<int>{1} << QList<int>{1}
                                                            << 1 << 1 << false << std::optional<ActionBuildError>{};        

    QTest::addRow("maximum_insignificant_digits_all_prt") << QString("0").repeated(MAX_LENGTH - 1) 
                                                              + "1.1" 
                                                              + QString("0").repeated(MAX_LENGTH - 1)
                                                            << QList<int>{1} << QList<int>{1}
                                                            << 1 << 1 << false << std::optional<ActionBuildError>{};                 
    // исключительные случаи
    QTest::addRow("no_int_prt") << "1." << QList<int>{1} << QList<int>{0} << 1 << 0 << false << std::optional<ActionBuildError>{ActionBuildError(INVALID_OPERAND_FORMAT)};
    QTest::addRow("no_fract_prt") << ".1" << QList<int>{0} << QList<int>{1} << 0 << 1 << false << std::optional<ActionBuildError>{ActionBuildError(INVALID_OPERAND_FORMAT)}; 
    QTest::addRow("no_point") << "1 1" << QList<int>{1} << QList<int>{1} << 0 << 1 << false << std::optional<ActionBuildError>{ActionBuildError(INVALID_OPERAND_FORMAT)};
    QTest::addRow("wrong_int_len") << "1" + QString("0").repeated(MAX_LENGTH) + ".1" 
                                      << QList<int>{1} << QList<int>{1} << 1 << 1 << false <<  std::optional<ActionBuildError>{ActionBuildError(INVALID_LENGTH)};
    QTest::addRow("wrong_fract_len") << "1." + QString("0").repeated(MAX_LENGTH) + "1" 
                                        << QList<int>{1} << QList<int>{1} << 1 << 1 << false <<  std::optional<ActionBuildError>{ActionBuildError(INVALID_LENGTH)};

    QTest::addRow("complex_number_1") << "12345.67890" 
                                      << QList<int>{5, 4, 3, 2, 1} 
                                      << QList<int>{6, 7, 8, 9} 
                                      << 5 << 4 << false << std::optional<ActionBuildError>{};
    QTest::addRow("complex_number_2") << "-9876.54321" 
                                      << QList<int>{6, 7, 8, 9} 
                                      << QList<int>{5, 4, 3, 2, 1} 
                                      << 4 << 5 << true << std::optional<ActionBuildError>{};

}

void BigRealNumberTest::fromStdString_tests() {
    QFETCH(QString, inputString);
    QFETCH(QList<int>, expectedIntPrt);
    QFETCH(QList<int>, expectedFractPrt);
    QFETCH(int, expectedIntPrtLen);
    QFETCH(int, expectedFractPrtLen);
    QFETCH(bool, expectedIsNegative);
    QFETCH(std::optional<ActionBuildError>, error);

    BigRealNumber result; 
    bool hasError = false;
    try {
       result = BigRealNumber::fromStdString(inputString.toStdString());
    } catch (const ActionBuildError &e) {
        hasError = true;
        QVERIFY(error.has_value());
        QCOMPARE(error.value(), e);
    }

    if (!hasError) {
        QCOMPARE(hasError, error.has_value());
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
}

void BigRealNumberTest::validateQString_tests_data() {
    QTest::addColumn<QString>("inputString");
    QTest::addColumn<bool>("isValid");

    QTest::addRow("simple_case") << "1.1" << true;

    // Корректные строки
    QTest::addRow("positive_number") << "123.456" << true;
    QTest::addRow("negative_number") << "-123.456" << true;
    QTest::addRow("zero") << "0.0" << true;
    QTest::addRow("max_int_part") << QString("1").repeated(MAX_LENGTH) + ".0" << true;
    QTest::addRow("max_fract_part") << "0." + QString("0").repeated(MAX_LENGTH) << true;

    // Некорректные строки
    QTest::addRow("no_decimal_point") << "123456" << false;
    QTest::addRow("multiple_decimal_points") << "123.45.6" << false;
    QTest::addRow("invalid_character_in_integer_part") << "12a.456" << false;
    QTest::addRow("invalid_character_in_fractional_part") << "123.45b" << false;
    QTest::addRow("too_long_integer_part") << QString("1").repeated(MAX_LENGTH + 1) + ".0" << false;
    QTest::addRow("too_long_fractional_part") << "1." + QString("0").repeated(MAX_LENGTH + 1) << false;
    QTest::addRow("negative_with_invalid_character") << "-12a.456" << false;
    QTest::addRow("empty_string") << "" << false;
    QTest::addRow("only_decimal_point") << "." << false;
    QTest::addRow("only_minus") << "-" << false;
    QTest::addRow("minus_with_decimal_point") << "-." << false;

    QTest::addRow("complex_valid_1") << "12345.67890" << true;
    QTest::addRow("complex_valid_2") << "-9876.54321" << true;
    QTest::addRow("complex_invalid_1") << "12.34.56" << false;
    QTest::addRow("complex_invalid_2") << "12a34.56" << false;
}

void BigRealNumberTest::validateQString_tests() {
    QFETCH(QString, inputString);
    QFETCH(bool, isValid);

    bool result = BigRealNumber::validateQString(inputString);
    qDebug() << inputString.left(5) << QString::number(isValid) << " --> "<< QString::number(result);
    QCOMPARE(result, isValid);
}

void BigRealNumberTest::toStdString_tests_data() {
    QTest::addColumn<std::vector<short>>("intPrt");
    QTest::addColumn<std::vector<short>>("fractPrt");
    QTest::addColumn<bool>("isNegative");
    QTest::addColumn<QString>("expectedString");

    QTest::addRow("simple_case") << std::vector<short>{1}
                                 << std::vector<short>{1}
                                 << true
                                 << "-1.1";

    QTest::addRow("max_int_len") << getVector(MAX_LENGTH, 0, false, 1)
                                    << std::vector<short>{1}
                                    << false
                                    << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 1, false);
                                 
    QTest::addRow("max_fract_len") << std::vector<short>{1}
                                      << getVector(MAX_LENGTH, 0, true, 1)
                                      << false
                                      << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 1, false);
    QTest::addRow("max_len") << getVector(MAX_LENGTH, 0, false, 1)
                                << getVector(MAX_LENGTH, 0, true, 1)
                                << true
                                << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, true);

    QTest::addRow("min_len") << std::vector<short>{0} 
                                << std::vector<short>{0} 
                                << false 
                                << "0.0";

    QTest::addRow("negative_number") << std::vector<short>{3, 2, 1} 
                                     << std::vector<short>{4, 5, 6} 
                                     << true
                                     << "-123.456";
    
    QTest::addRow("positive_number") << std::vector<short>{3, 2, 1} 
                                     << std::vector<short>{4, 5, 6} 
                                     << false
                                     << "123.456";

    QTest::addRow("complex_number_1") << std::vector<short>{5, 4, 3, 2, 1}
                                      << std::vector<short>{6, 7, 8, 9, 0}
                                      << false
                                      << "12345.67890";
    QTest::addRow("complex_number_2") << std::vector<short>{6, 7, 8, 9}
                                      << std::vector<short>{5, 4, 3, 2, 1}
                                      << true
                                      << "-9876.54321";
}

void BigRealNumberTest::toStdString_tests() {
    QFETCH(std::vector<short>, intPrt);
    QFETCH(std::vector<short>, fractPrt);
    QFETCH(bool, isNegative);
    QFETCH(QString, expectedString);

    BigRealNumber brn(intPrt, fractPrt, isNegative);
    QString resultString = QString::fromStdString(brn.toStdString());
    qDebug() << expectedString.left(5) << " --> "<< resultString.left(5);
    QCOMPARE(resultString, expectedString);
}

void BigRealNumberTest::operatorAdd_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");
    QTest::addColumn<std::optional<ActionPerformError>>("expectedError");

    QTest::addRow("simple_case") << "1.1" << "2.2" << "3.3" << std::optional<ActionPerformError>{};


    QTest::addRow("max_len_int_operands") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 1, false) 
                                             << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 1, false) 
                                             << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 2, false)
                                             << std::optional<ActionPerformError>{};
                
    QTest::addRow("max_len_fract_operands") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 1, false) 
                                               << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 1, false) 
                                               << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 2, 2, false)
                                               <<std::optional<ActionPerformError>{};
                                                        

    QTest::addRow("max_len_operands") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                         << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                         << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 2, 2, false)
                                         << std::optional<ActionPerformError>{};
    QTest::addRow("min_len_operands") << "1.0" << "1.0" << "2.0" << std::optional<ActionPerformError>{};

    QTest::addRow("max_len_int_res") << genQStrNumb_m1xp0x1(MAX_LENGTH-1, 0, 9, 1, false) 
                                        << genQStrNumb_m1xp0x1(MAX_LENGTH-1, 0, 1, 1, false) 
                                        << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 2, false) 
                                        << std::optional<ActionPerformError>{};
    
    
    QTest::addRow("second_operand_len_more") << "0.0" << "0.01" << "0.01" << std::optional<ActionPerformError>{};
    QTest::addRow("first_operand_len_more") << "0.01" << "0.0" << "0.01" << std::optional<ActionPerformError>{};

    QTest::addRow("pos_neg_operands_pos_res") << "2.0" << "-1.0" << "1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_pos_operands_pos_res") << "-1.0" << "2.0" << "1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_pos_operands_neg_res") << "-2.0" << "1.0" << "-1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_neg_operands_neg_res") << "-1.0" << "-1.0" << "-2.0" << std::optional<ActionPerformError>{};
    QTest::addRow("null_res") << "1.0" << "-1.0" << "0.0" << std::optional<ActionPerformError>{};


    QTest::addRow("max_int_with_carry") << QString("9").repeated(MAX_LENGTH-1) + ".9"
                                        << "0.1"
                                        << QString("1") + QString("0").repeated(MAX_LENGTH-1) + ".0"
                                        << std::optional<ActionPerformError>{};

    QTest::addRow("small_fractional_carry") << "0.999" << "0.001" << "1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("max_fract_carry") << "0." + QString("9").repeated(MAX_LENGTH) 
                                     << "0." + QString("0").repeated(MAX_LENGTH-1) + "1" 
                                     << "1.0"
                                     << std::optional<ActionPerformError>{};

    QTest::addRow("int_and_fraction_carry") << "999.999" << "0.002" << "1000.001" << std::optional<ActionPerformError>{};
    QTest::addRow("max_int_and_fraction_len_carry") << QString("9").repeated(MAX_LENGTH-1) 
                                                        + "."  
                                                        + QString("9").repeated(MAX_LENGTH)
                                                    << "0." + QString("0").repeated(MAX_LENGTH-1) + "1" 
                                                    << "1" + QString("0").repeated(MAX_LENGTH-1) + ".0"
                                                    << std::optional<ActionPerformError>{};
    QTest::addRow("complex_add_1") << "123.456" << "789.012" << "912.468" << std::optional<ActionPerformError>{};
    QTest::addRow("complex_add_2") << "-123.456" << "789.012" << "665.556" << std::optional<ActionPerformError>{};

    QTest::addRow("int_overwlow_test") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                       << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 9, 0, false) 
                                       << "0.0" 
                                       << std::optional<ActionPerformError>{ActionPerformError(INTEGER_PART_OVERFLOW)};

}

void BigRealNumberTest::operatorAdd_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);
    QFETCH(std::optional<ActionPerformError>, expectedError);

    bool hasError = false;
    BigRealNumber r;
    try {
        r = BigRealNumber::fromStdString(a.toStdString())
                    + BigRealNumber::fromStdString(b.toStdString());
        qDebug() << a.left(5) << " + " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    } catch (ActionPerformError &actualError) {
        QVERIFY(expectedError.has_value());
        QCOMPARE(actualError, expectedError.value());
        hasError = true;
    }

    if (hasError) {
        QCOMPARE(r.toStdString(), res.toStdString());
    }
}

void BigRealNumberTest::operatorSub_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");
    QTest::addColumn<std::optional<ActionPerformError>>("expectedError");

    QTest::addRow("simple_case") << "3.3" << "1.1" << "2.2" << std::optional<ActionPerformError>{};;

    // test len operands
    QTest::addRow("max_operands") << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                  << genQStrNumb_m1xp0x1(MAX_LENGTH, MAX_LENGTH, 1, 1, false)
                                  << "0.0"
                                  << std::optional<ActionPerformError>{};
    QTest::addRow("min_operands") << "1.0" << "1.0" << "0.0" << std::optional<ActionPerformError>{};
    
    QTest::addRow("second_operand_len_more") << "0.0" << "0.01" << "-0.01" << std::optional<ActionPerformError>{};
    QTest::addRow("first_operand_len_more") << "0.01" << "0.0" << "0.01" << std::optional<ActionPerformError>{};

    // test 
    QTest::addRow("pos_neg_operands_pos_res") << "2.0" << "-1.0" << "3.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_pos_operands_neg_res") << "-1.0" << "2.0" << "-3.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_pos_operands_neg_res") << "-2.0" << "1.0" << "-3.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_neg_operands_pow_res") << "-1.0" << "-2.0" << "1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("pos_pos_operand_null_res") << "1.0" << "1.0" << "0.0" << std::optional<ActionPerformError>{};

    //cary tests
    QTest::addRow("max_int_with_carry") << QString("1") + QString("0").repeated(MAX_LENGTH-1) + ".0"
                                        << "1.0"
                                        << QString("9").repeated(MAX_LENGTH-1) + ".0"
                                        << std::optional<ActionPerformError>{};

    QTest::addRow("small_fractional_carry") << "1.0" << "0.001" << "0.999" << std::optional<ActionPerformError>{};
    QTest::addRow("max_fract_carry") << "1.0" << "0." + QString("9").repeated(MAX_LENGTH) 
                                     << "0." + QString("0").repeated(MAX_LENGTH-1) + "1"
                                     << std::optional<ActionPerformError>{};

    QTest::addRow("int_and_fract_carry") << "1000.001" << "0.002" << "999.999" << std::optional<ActionPerformError>{};

    QTest::addRow("max_int_and_fract_len_carry") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                 << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                                 << QString("9").repeated(MAX_LENGTH-1) 
                                                    + "."
                                                    + QString("9").repeated(MAX_LENGTH)
                                                << std::optional<ActionPerformError>{};

    QTest::addRow("complex_sub_1") << "789.012" << "123.456" << "665.556" << std::optional<ActionPerformError>{};
    QTest::addRow("complex_sub_2") << "-123.456" << "-789.012" << "665.556" << std::optional<ActionPerformError>{};

    QTest::addRow("int_overwlow_test") << QString("9").repeated(MAX_LENGTH) + ".0"
                                        << "1.0"
                                        << "0.0" 
                                        << std::optional<ActionPerformError>{ActionPerformError(INTEGER_PART_OVERFLOW)};

}

void BigRealNumberTest::operatorSub_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);
    QFETCH(std::optional<ActionPerformError>, expectedError);

    bool hasError = false;
    BigRealNumber r;
    try {
        r = BigRealNumber::fromStdString(a.toStdString())
                    - BigRealNumber::fromStdString(b.toStdString());
        qDebug() << a.left(5) << " - " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    } catch (ActionPerformError &actualError) {
        QVERIFY(expectedError.has_value());
        QCOMPARE(actualError, expectedError.value());
        hasError = true;
    }

    if (hasError) {
        QCOMPARE(r.toStdString(), res.toStdString());
    }
}   

void BigRealNumberTest::operatorMul_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");
    QTest::addColumn<std::optional<ActionPerformError>>("expectedError");


    QTest::addRow("simple_case_1") << "2.0" << "2.0" << "4.0" << std::optional<ActionPerformError>{};
    QTest::addRow("simple_case_2") << "0.1" << "0.1" << "0.01" << std::optional<ActionPerformError>{};

    QTest::addRow("max_len_int_res") << genQStrNumb_m1xp0x1((MAX_LENGTH-10)+1, 0, 1, 0, false)
                                        << genQStrNumb_m1xp0x1((MAX_LENGTH-991)+1, 0, 1, 0, false)
                                        << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false)
                                        << std::optional<ActionPerformError>{};
    QTest::addRow("max_len_fract_operand") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                              << "1.0" 
                                              << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false)
                                              << std::optional<ActionPerformError>{};

    QTest::addRow("null_pos_operands_null_res") << "0.0" << "1.0" << "0.0" << std::optional<ActionPerformError>{};
    QTest::addRow("pos_null_operands_null_res") << "1.0" << "0.0" << "0.0" << std::optional<ActionPerformError>{};

    QTest::addRow("pos_neg_operands_neg_res") << "1.0" << "-1.0" << "-1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_pos_operands_neg_res") << "-1.0" << "1.0" << "-1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_neg_operands_pos_res") << "-1.0" << "-1.0" << "1.0" << std::optional<ActionPerformError>{};

    QTest::addRow("small_fractional_carry") << "0.9" << "0.9" << "0.81" << std::optional<ActionPerformError>{};

    QTest::addRow("int_and_fraction_carry") << "99.9" << "0.1" << "9.99" << std::optional<ActionPerformError>{};
    
    QTest::addRow("max_int_len_res_with_carry") << genQStrNumb_m1xp0x1(MAX_LENGTH-1, 0, 1, 0, false) 
                                                << "10.0" 
                                                << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false)
                                                << std::optional<ActionPerformError>{}; 

    QTest::addRow("max_fract_len_res_with_carry") << "0." + QString("1").repeated(MAX_LENGTH) 
                                                  << "10.0"
                                                  << "1." + QString("1").repeated(MAX_LENGTH-1)
                                                  << std::optional<ActionPerformError>{};

    QTest::addRow("max_len_res_with_carry") << QString("1").repeated(MAX_LENGTH-1) 
                                                + "." 
                                                + QString("1").repeated(MAX_LENGTH)
                                            << "10.0"
                                            << QString("1").repeated(MAX_LENGTH)  
                                                + "."  
                                                + QString("1").repeated(MAX_LENGTH-1)
                                            << std::optional<ActionPerformError>{};

    QTest::addRow("complex_mul_1") << "12.34" << "56.78" << "700.6652" << std::optional<ActionPerformError>{};
    QTest::addRow("complex_mul_2") << "-12.34" << "56.78" << "-700.6652" << std::optional<ActionPerformError>{};

    QTest::addRow("int_overwlow_test") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                       << "10.0"
                                       << "0.0" 
                                       << std::optional<ActionPerformError>{ActionPerformError(INTEGER_PART_OVERFLOW)};
 }
 
void BigRealNumberTest::operatorMul_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);
    QFETCH(std::optional<ActionPerformError>, expectedError);

    bool hasError = false;
    BigRealNumber r;
    try {
        r = BigRealNumber::fromStdString(a.toStdString())
                    * BigRealNumber::fromStdString(b.toStdString());
        qDebug() << a.left(5) << " * " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    } catch (ActionPerformError &actualError) {
        QVERIFY(expectedError.has_value());
        QCOMPARE(actualError, expectedError.value());
        hasError = true;
    }

    if (hasError) {
        QCOMPARE(r.toStdString(), res.toStdString());
    }
}

void BigRealNumberTest::operatorDiv_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("res");
    QTest::addColumn<std::optional<ActionPerformError>>("expectedError");

    QTest::addRow("simple_case") << "2.0" << "2.0" << "1.0" << std::optional<ActionPerformError>{};
    

    QTest::addRow("max_len_int_divider_max_len_fract_res") << "1.0" 
                                                           << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false)  
                                                           << genQStrNumb_m1xp0x1(0, MAX_LENGTH-1, 0, 1, false)
                                                           << std::optional<ActionPerformError>{};

    QTest::addRow("max_len_int_dividend_0_5_divider") << genQStrNumb_m1xp0x1(MAX_LENGTH-1, 0, 5, 0, false)
                                                      << "0.5"
                                                      << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false)
                                                      << std::optional<ActionPerformError>{};

    
    QTest::addRow("cyclic_fraction_res") << "1.0" << "3.0" 
                                         << QString('0') + QString('.') + QString("3").repeated(1000)
                                         << std::optional<ActionPerformError>{};

    QTest::addRow("null_pos_operands_null_res") << "0.0" << "1.0" << "0.0" << std::optional<ActionPerformError>{};

    QTest::addRow("pos_neg_operands_neg_res") << "1.0" << "-1.0" << "-1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_pos_operands_neg_res") << "-1.0" << "1.0" << "-1.0" << std::optional<ActionPerformError>{};
    QTest::addRow("neg_neg_operands_pos_res") << "-1.0" << "-1.0" << "1.0" << std::optional<ActionPerformError>{};
    
    QTest::addRow("max_len_int_res") << genQStrNumb_m1xp0x1(MAX_LENGTH-1, 0, 1, 0, false)
                                     << "0.1"
                                     << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false)
                                     << std::optional<ActionPerformError>{};
    QTest::addRow("max_len_fract_res") << "0.1" + QString("0").repeated(MAX_LENGTH-2) + "1"
                                       << "0.1"
                                       << "1." + QString("0").repeated(MAX_LENGTH-2) + "1"
                                       << std::optional<ActionPerformError>{};
    QTest::addRow("max_len_res") << "1" 
                                     + QString("0").repeated(MAX_LENGTH-2) 
                                     + "."
                                     + QString("0").repeated(MAX_LENGTH-1)
                                     + "1"
                                 << "0.1"
                                 << "1" 
                                     + QString("0").repeated(MAX_LENGTH-1) 
                                     + "."
                                     + QString("0").repeated(MAX_LENGTH-2)
                                     + "1"
                                 << std::optional<ActionPerformError>{};
    QTest::addRow("complex_div_1") << "100.0" << "4.0" << "25.0" << std::optional<ActionPerformError>{};
    QTest::addRow("complex_div_2") << "-100.0" << "4.0" << "-25.0" << std::optional<ActionPerformError>{};

    QTest::addRow("int_overwlow") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 5, 0, false) 
                                       << "0.5"
                                       << "0.0" 
                                       << std::optional<ActionPerformError>{ActionPerformError(INTEGER_PART_OVERFLOW)};

    QTest::addRow("div_by_zero") << "1.0"
                                        << "0.0"
                                        << "0.0" 
                                        << std::optional<ActionPerformError>{ActionPerformError(DIVISION_BY_ZERO)};
                                       
}

void BigRealNumberTest::operatorDiv_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(QString, res);
    QFETCH(std::optional<ActionPerformError>, expectedError);


    bool hasError = false;
    BigRealNumber r;
    try {
        r = BigRealNumber::fromStdString(a.toStdString())
                    / BigRealNumber::fromStdString(b.toStdString());
        qDebug() << a.left(5) << " / " << b.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    } catch (ActionPerformError &actualError) {
        QVERIFY(expectedError.has_value());
        QCOMPARE(actualError, expectedError.value());
        hasError = true;
    }

    if (hasError) {
        QCOMPARE(r.toStdString(), res.toStdString());
    }
}

void BigRealNumberTest::pow_tests_data() {
    QTest::addColumn<QString>("b");
    QTest::addColumn<QString>("p");
    QTest::addColumn<QString>("res");
    QTest::addColumn<std::optional<ActionPerformError>>("expectedError");

    QTest::addRow("simple_case") << "2.0" << "3.0" << "8.0" << std::optional<ActionPerformError>{};

    QTest::addRow("ten_pow") << "10.0" << "10.0" << "10000000000.0" << std::optional<ActionPerformError>{};

    QTest::addRow("ten_pow") << "10.0" << "10.0" << "10000000000.0" << std::optional<ActionPerformError>{};

    QTest::addRow("neg_base_even_pow") << "-2.0" << "2.0" << "4.0" << std::optional<ActionPerformError>{};

    QTest::addRow("neg_base_odd_pow") << "-2.0" << "3.0" << "-8.0" << std::optional<ActionPerformError>{};

    QTest::addRow("0_1_base_max_len_res") << "0.1" 
                                          << QString::number(MAX_LENGTH) + ".0" 
                                          << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false)
                                          << std::optional<ActionPerformError>{};

    QTest::addRow("10_base_max_len_int_res") << "10.0" << "999.0" 
                                               <<  QString("1") + QString("0").repeated(MAX_LENGTH-1) + QString(".0")
                                               << std::optional<ActionPerformError>{};
    

    QTest::addRow("negative_pow") << "1.0" << "-1.0" << "0.0" << std::optional<ActionPerformError>{ActionPerformError(OPERAND_LESS_ZERO_POW_FACT)};
    QTest::addRow("pow_with_fract") << "1.0" << "1.1" << "0.0" << std::optional<ActionPerformError>{ActionPerformError(OPERAND_WITH_FRACTIONAL_PART_POW_FACT)};
}


void BigRealNumberTest::pow_tests() {
    QFETCH(QString, b);
    QFETCH(QString, p);
    QFETCH(QString, res);
    QFETCH(std::optional<ActionPerformError>, expectedError);

    bool hasError = false;
    BigRealNumber r;
    try {
        BigRealNumber r = BigRealNumber::fromStdString(b.toStdString())
                        .pow(BigRealNumber::fromStdString(p.toStdString()));
        qDebug() << b.left(5) << " ** " << p.left(5) << " = " << QString::fromStdString(r.toStdString()).left(5);
    } catch (ActionPerformError &actualError) {
        QVERIFY(expectedError.has_value());
        QCOMPARE(actualError, expectedError.value());
        hasError = true;
    }

    if (hasError) {
        QCOMPARE(r.toStdString(), res.toStdString());
    }
}

void BigRealNumberTest::factorial_tests_data() {
    QTest::addColumn<QString>("f");
    QTest::addColumn<QString>("res");
    QTest::addColumn<std::optional<ActionPerformError>>("expectedError");

    QTest::addRow("simple_case") << "5.0" << "120.0" << std::optional<ActionPerformError>{};
    
    QTest::addRow("negative_fact") << "-1.0" << "0.0" << std::optional<ActionPerformError>{ActionPerformError(OPERAND_LESS_ZERO_POW_FACT)};
    QTest::addRow("pow_with_fract") << "1.1" << "0.0" << std::optional<ActionPerformError>{ActionPerformError(OPERAND_WITH_FRACTIONAL_PART_POW_FACT)};
}


void BigRealNumberTest::factorial_tests() {
    QFETCH(QString, f);
    QFETCH(QString, res);
    QFETCH(std::optional<ActionPerformError>, expectedError);

    bool hasError = false;
    BigRealNumber r;
    try {
        BigRealNumber r = BigRealNumber::fromStdString(f.toStdString()).factorial();
        qDebug() << "fact(" << f.left(5) << ")" << " = " << QString::fromStdString(r.toStdString()).left(5);
    } catch (ActionPerformError &actualError) {
        QVERIFY(expectedError.has_value());
        QCOMPARE(actualError, expectedError.value());
        hasError = true;
    }

    if (hasError) {
        QCOMPARE(r.toStdString(), res.toStdString());
    }
}



void BigRealNumberTest::operatorEq_tests_data() {
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

void BigRealNumberTest::operatorEq_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             == BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " == " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}


void BigRealNumberTest::operatorMore_tests_data() {
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

    QTest::addRow("max_fract_operands_first_more") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 2, false) 
                                                   << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false)
                                                   << true;

    QTest::addRow("max_fract_operands_second_more") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                                    << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 2, false)
                                                    << false;

    QTest::addRow("neg_neg_operand_first_abs_more") << "-2.0" << "-1.0" << false;
    QTest::addRow("neg_neg_operand_second_abs_more") << "-1.0" << "-2.0" << true;
    QTest::addRow("pos_neg_operand_second_abs_more") << "1.0" << "-3.0" << true;
    QTest::addRow("neg_pos_operand_first_abs_more") << "-3.0" << "-2.0" << false;
}

void BigRealNumberTest::operatorMore_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             > BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " > " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}

void BigRealNumberTest::operatorNotEq_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<bool>("res");

    QTest::addRow("simple_case_1") << "1.0" << "1.0" << false;
    QTest::addRow("simple_case_2") << "2.0" << "1.0" << true;

    QString buf = genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0);
    QTest::addRow("max_len_int_operands") << buf << buf << false;
    buf = genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1);
    QTest::addRow("max_len_fract_operands") << buf << buf << false; 

    QTest::addRow("neg_pos_operands") << "-1.0" << "1.0" << true;
}

void BigRealNumberTest::operatorNotEq_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             != BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " != " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}

void BigRealNumberTest::operatorLess_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<bool>("res");

    QTest::addRow("simple_case_1") << "1.0" << "2.0" << true;
    QTest::addRow("simple_case_2") << "1.0" << "0.0" << false;

    QTest::addRow("max_int_operands_first_less") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                 << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                 << true;
    QTest::addRow("max_int_operands_second_less") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                  << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                  << false;

    QTest::addRow("max_fract_operands_first_less") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                                   << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 2, false)
                                                   << true;
    QTest::addRow("max_fract_operands_second_less") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 2, false) 
                                                    << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false)
                                                    << false;

    QTest::addRow("neg_neg_operand_first_abs_less") << "-1.0" << "-2.0" << false;
    QTest::addRow("neg_neg_operand_second_abs_less") << "-2.0" << "-1.0" << true;
    QTest::addRow("pos_neg_operand_first_abs_less") << "-3.0" << "1.0" << true;
    QTest::addRow("neg_pos_operand_first_abs_less") << "-2.0" << "-3.0" << false;
}

void BigRealNumberTest::operatorLess_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             < BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " < " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}

void BigRealNumberTest::operatorLessEq_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<bool>("res");

    QTest::addRow("simple_case_1") << "1.0" << "2.0" << true;
    QTest::addRow("simple_case_2") << "1.0" << "1.0" << true;
    QTest::addRow("simple_case_3") << "2.0" << "1.0" << false;

    QTest::addRow("max_int_operands_first_less_eq") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                    << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                    << true;
    QTest::addRow("max_int_operands_second_less_eq") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                     << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                     << false;

    QTest::addRow("max_fract_operands_first_less_eq") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                                      << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 2, false)
                                                      << true;
    QTest::addRow("max_fract_operands_second_less_eq") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 2, false) 
                                                       << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false)
                                                       << false;
    QTest::addRow("max_fract_operands_eq") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false) 
                                            << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 0, 1, false)
                                            << true;


    QTest::addRow("neg_neg_operand_first_abs_less_eq") << "-1.0" << "-2.0" << false;
    QTest::addRow("neg_neg_operand_second_abs_less_eq") << "-2.0" << "-1.0" << true;
    QTest::addRow("pos_neg_operand_first_abs_less_eq") << "-3.0" << "1.0" << true;
    QTest::addRow("neg_pos_operand_first_abs_less_eq") << "-2.0" << "-3.0" << false;
}

void BigRealNumberTest::operatorLessEq_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             <= BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " <= " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}

void BigRealNumberTest::operatorMoreEq_tests_data() {
    QTest::addColumn<QString>("a");
    QTest::addColumn<QString>("b");
    QTest::addColumn<bool>("res");

    QTest::addRow("simple_case_1") << "2.0" << "1.0" << true;
    QTest::addRow("simple_case_2") << "1.0" << "1.0" << true;
    QTest::addRow("simple_case_3") << "0.0" << "1.0" << false;

    QTest::addRow("max_int_operands_first_more_eq") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                    << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                    << true;
    QTest::addRow("max_int_operands_second_more_eq") << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 1, 0, false) 
                                                     << genQStrNumb_m1xp0x1(MAX_LENGTH, 0, 2, 0, false) 
                                                     << false;
    QTest::addRow("max_fract_operands_first_more_eq") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 2, 0, false) 
                                                      << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 0, false)
                                                      << true;
    QTest::addRow("max_fract_operands_second_more_eq") << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 1, 0, false) 
                                                       << genQStrNumb_m1xp0x1(0, MAX_LENGTH, 2, 0, false)
                                                       << false;
    QTest::addRow("neg_neg_operand_first_abs_more_eq") << "-2.0" << "-1.0" << false;
    QTest::addRow("neg_neg_operand_second_abs_more_eq") << "-1.0" << "-2.0" << true;
    QTest::addRow("pos_neg_operand_first_abs_more_eq") << "1.0" << "-3.0" << true;
    QTest::addRow("neg_pos_operand_first_abs_more_eq") << "-3.0" << "-2.0" << false;
}

void BigRealNumberTest::operatorMoreEq_tests() {
    QFETCH(QString, a);
    QFETCH(QString, b);
    QFETCH(bool, res);
    bool r = BigRealNumber::fromStdString(a.toStdString()) 
             >= BigRealNumber::fromStdString(b.toStdString());
    qDebug() << "(" << a.left(5) << " >= " << b.left(5) << ") = " << QString::number(r);
    QCOMPARE(r, res);
}

#include "BigRealNumberTests.moc"
