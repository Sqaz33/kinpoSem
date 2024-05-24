#include "ActionsFromXMLTests.h"

void ActionFromXMLTests::tests_data() {
    QTest::addColumn<QString>("path");
    QTest::addColumn<QList<Action>>("actions");
    QTest::addColumn<QList<int>>("actionsNumb");
    
    QTest::addColumn<bool>("isError");

    QTest::addRow("simple_case") << "C:/kinpoSem/tests/xml/simple_case_test.xml"
                                << QList<Action>{
                                    Action(
                                        MUL,
                                        &BigRealNumber::fromStdString("2.5"),
                                        &BigRealNumber::fromStdString("3.7")
                                    ),
                                    Action(
                                        FACT,
                                        &BigRealNumber::fromStdString("5.0")
                                    )
                                }
                                << QList<int>{1, 2}
                                << false;
    }


void ActionFromXMLTests::tests() {
    QFETCH(QString, path);
    QFETCH(QList<Action>, actions);
    QFETCH(QList<int>, actionsNumb);
    QFETCH(bool, isError);
    QList<ActionError> errorList;

    // bool isError = false;
    // try {
        ActionsFromXML reader(path.toStdString(), &errorList);
    // }

    const QHash<int, Action*>* XMLActions = reader.getActions();
    QList<int> keys = XMLActions->keys();
    qSort(keys.begin(), keys.end());

    QCOMPARE(actionsNumb.length(), keys.length());
    for (int i = 0; i < actionsNumb.length(); i++) {
        QCOMPARE(actionsNumb.at(i), keys.at(i));
        QCOMPARE(actions.at(i), XMLActions->value(keys.at(i)));
    }

}

#include "ActionsFromXMLTests.moc"