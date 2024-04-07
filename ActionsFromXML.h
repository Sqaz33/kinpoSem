#pragma once

#include "string"

#include "qlist"
#include "qXmlStreamReader"
#include "stdexcept"
#include "qFile"
#include "Action.h"
using namespace std;


class ActionsFromXML {
private:
	QList<Action> actions;

	void loadActions(const string& XMLPath);
public:
	ActionsFromXML(const string& XMLPath);

	const QList<Action>& getActions() const;
};

