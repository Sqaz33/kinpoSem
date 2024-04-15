#pragma once

#include "string"
#include "stdexcept"

#include "qlist"
#include "qXmlStreamReader"
#include "qFile"

#include "Action.h"
using namespace std;


class ActionsFromXML {
private:
	QHash<int, Action*> actions;
	QList<ActionError>* actionErrors;

	void loadActions(const string& XMLPath);
public:
	ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors);

	const QHash<int, Action*>* getActions() const;
};

