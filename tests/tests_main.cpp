#include <QtTest/QtTest>
#include "BigRealNumberTests.h"
#include "ActionsFromXMLTests.h"

int main(int argc, char *argv[]) {
    int status = 0;
    // // run tests for BigRealNumber
    // {
    //     BigRealNumberTest brnTests;
    //     status |= QTest::qExec(&brnTests, argc, argv);
    // }

    // run tests for ActionFromXML
    {
        ActionFromXMLTests actionFromXMLTests;
        status |= QTest::qExec(&actionFromXMLTests, argc, argv);
    }



    return status;
}