#pragma once

#include "string"

#include "qlist"
#include "qXmlStreamReader"
#include "qFile"
#include "Action.h"
using namespace std;


class ActionsFromXML {
private:
	string path;
	QList<Action> actions;

	void setPath(const string& XMLPath);
	void loadActions();

public:
	ActionsFromXML(const string& XMLPath);

	const QList<Action>& getActions() const;
};

