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
	QList<Action*> actions;
	QList<string>* actionErrors;

	void loadActions(const string& XMLPath);
public:
	ActionsFromXML(const string& XMLPath, QList<string>* actionErrors);

	const QList<Action*>* getActions() const;
};

