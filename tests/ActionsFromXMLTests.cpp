#include "ActionsFromXMLTests.h"

void ActionFromXMLTests::tests_data() {
    QTest::addColumn<QString>("path");
    QTest::addColumn<qh>("expectedActions");
    QTest::addColumn<QList<ActionError>>("expectedErrors");

    QTest::addRow("simple_case") 
        << "../../../../../tests/xml/simple_case_test.xml"
        << QHash<int, Action>{
            {1, Action(MUL, &BigRealNumber::fromStdString("2.5"), &BigRealNumber::fromStdString("3.7"))},
            {2, Action(FACT, &BigRealNumber::fromStdString("5.0"))}
        }
        << QList<ActionError>{};

    QTest::addRow("invalid_arity")
        << "../../../../../tests/xml/invalid_arity_test.xml"
        << QHash<int, Action>{}
        << QList<ActionError>{ActionBuildError(INVALID_ARITY)};

    QTest::addRow("unknown_operator")
        << "../../../../../tests/xml/unknown_operator_test.xml"
        << QHash<int, Action>{}
        << QList<ActionError>{ActionBuildError(NO_OPER_E)};

    QTest::addRow("missing_operand")
        << "../../../../../tests/xml/missing_operand_test.xml"
        << QHash<int, Action>{}
        << QList<ActionError>{ActionBuildError(INVALID_ARITY)};
}

void ActionFromXMLTests::tests() {
    QFETCH(QString, path);
    QFETCH(qh, expectedActions);
    QFETCH(QList<ActionError>, expectedErrors);

    QList<ActionError> actualErrors;
    ActionsFromXML reader(path.toStdString(), &actualErrors);
    
    if (actualErrors.size() > 0) {
        QCOMPARE(actualErrors.size(), expectedErrors.size());
        for (int i = 0; i < expectedErrors.size(); ++i) {
            QCOMPARE(actualErrors[i], expectedErrors[i]);
        }
    }
    
    if (expectedErrors.size() == 0) {
        const QHash<int, const Action*>* actualActions = reader.getActions();

        QCOMPARE(actualActions->size(), expectedActions.size());

        for (auto it = expectedActions.begin(); it != expectedActions.end(); ++it) {
            int key = it.key();
            Action expectedAction = it.value();
            QVERIFY(actualActions->contains(key));
            if (actualActions->contains(key)) {
                QCOMPARE(*actualActions->value(key), expectedAction);
            }
        }
    }
}

#include "ActionsFromXMLTests.moc"
