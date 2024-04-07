#include "ActionsFromXML.h"

ActionsFromXML::ActionsFromXML(const string& XMLPath) {
	actions = QList<Action>();
	loadActions(XMLPath);
}


const QList<Action>& ActionsFromXML::getActions() const {
	return actions;
}

void ActionsFromXML::loadActions(const string& XMLPath) {
	QString pt = QString::fromStdString(XMLPath);
	QFile file(pt);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw runtime_error("Ошибка чтения: неверно указан путь");
	}

	
	QXmlStreamReader reader(&file);
}
