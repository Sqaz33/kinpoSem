#ifndef ACTION_FROM_XML_TESTS
#define ACTION_FROM_XML_TESTS

#include <QtTest/QtTest>

#include "../include/ActionsFromXML.h"
#include "../include/Action.h"
#include "../include/ActionError.h"
#include "../include/BigRealNumber.h"

#include <QString>
#include <QList>
#include <QHash>

Q_DECLARE_METATYPE(Action)
Q_DECLARE_METATYPE(Action*)

// tests for ActionsFromXML::ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors)
class ActionFromXMLTests : public QObject {
    Q_OBJECT
private slots:
    // simple case test
    void tests_data();
    void tests();
};

#endif
