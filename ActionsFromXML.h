#pragma once

#include "string"

#include "qlist"
#include "qXmlStreamReader"
#include "qFile";
#include "Action.h"
using namespace std;


class ActionsFromXML {
private:
	string path;
	QList<Action> actions;

	void setPath(string& XMLPath);
	void loadActions();
public:
	ActionsFromXML(string& XMLPath);

	QList<Action> getActions();
};

