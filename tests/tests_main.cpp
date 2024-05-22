#include <QtTest/QtTest>
#include "BigRealNumberTests.h"

int main(int argc, char *argv[]) {
    int status = 0;

    // run tests for BigRealNumberTest
    {
        BigRealNumberTest brnTests;
        status |= QTest::qExec(&brnTests, argc, argv);
    }


    return status;
}