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
	QList<ActionBuildError>* actionErrors;

	void loadActions(const string& XMLPath);
public:
	ActionsFromXML(const string& XMLPath, QList<ActionBuildError>* actionErrors);

	const QHash<int, Action*>* getActions() const;
};

