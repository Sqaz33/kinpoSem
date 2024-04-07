#include "iostream"

#include "BigRealNumber.h"
#include "Action.h"
#include "ActionsFromXML.h"
#include "ResultActionsToTxt.h"

int main() {
	try {
		QString path = "test.xml";
		ActionsFromXML input(path.toStdString());
		const QList<Action*>* l = input.getActions();
	} catch (const runtime_error& e) {
		cout << e.what();
	}
}