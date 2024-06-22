#ifndef ACTIONS_FROM_XML_TESTS
#define ACTIONS_FROM_XML_TESTS

#include <QtTest/QtTest>

#include "../include/ActionsFromXML.h"
#include "../include/Action.h"
#include "../include/ActionError.h"
#include "../include/BigRealNumber.h"

#include <string>

#include <QString>
#include <QList>
#include <QHash>
#include <QtAlgorithms>


typedef QHash<int, Action> qh;

Q_DECLARE_METATYPE(QList<ActionError>)
Q_DECLARE_METATYPE(QList<ActionBuildError>)
Q_DECLARE_METATYPE(qh)


// tests for ActionsFromXML::ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors)
class ActionFromXMLTests : public QObject {
    Q_OBJECT
private slots:
    // simple case test
    void tests_data();
    void tests();
};

#endif
