#include "ActionFromXMLTests.h"

void ActionFromXMLTests::tests_data() {
    QTest::addColumn<QString>("path");
    QTest::addColumn<QList<Action>>("actions");
    QTest::addColumn<QList<int>>("actions_numbers");
    
    QTest::addColumn<bool>("isError");

    QTest::addRow("simple_case") << "simple_case_test.xml" 
                                 <<  QList<Action>{ 
                                        Action(
                                            MUL, 
                                            &BigRealNumber::fromStdString("2.5"),
                                            &BigRealNumber::fromStdString("3.7")
                                        ),
                                        Action(
                                            FACT, 
                                            &BigRealNumber::fromStdString("5.0"),
                                        )
                                    }
                                 << QList<int>{1, 2}
                                 << false;
    }


void ActionFromXMLTests::tests() {
    QFETCH(QString, path);
    QFETCH(QList<Action>, actions);
    QFETCH(QList<int>, actions_numbers);
    QFETCH(bool, isError);

    ActionsFromXML reader(path.toStdString(), &QList<ActionError>{});
    const QHash<int, Action*>* actions = reader.getActions();
    QCOMPARE(actions_numbers.length(), actions->keys().length());
    for (int i: actions->keys()) {
        QCOMPARE(k, qlist)
    }

}

#include "ActionFromXMLTests.moc"