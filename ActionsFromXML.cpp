#include "ActionsFromXML.h"

ActionsFromXML::ActionsFromXML(const string& XMLPath, QList<string>* actionErrors) {
	this->actionErrors = actionErrors;
	actions = QList<Action*>();
	loadActions(XMLPath);
}

const QList<Action*>* ActionsFromXML::getActions() const {
	return &actions;
}

void ActionsFromXML::loadActions(const string& XMLPath) {
	QString pt = QString::fromStdString(XMLPath);
	QFile file(pt);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw runtime_error("Ошибка записи: неверно указан путь выходного файла");
	}

	QXmlStreamReader reader(&file);
	string term1;
	string term2;
	string oper;

	while (!reader.atEnd() && !reader.hasError()) {
		reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "operation") {
			reader.readNext();
			term2 = "0.0";
			while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "operation")) {
				reader.readNext();
				string txt = reader.readElementText().toStdString();
				if (reader.name() == "operand1") {
					term1 = txt;
				} else if (reader.name() == "operand2") {
					term2 = txt;
				} else if (reader.name() == "operator") {
					oper = txt;
				}
			}
			try {
				Action *act = &Action::fromStdStrings(term1, term2, oper);
				actions.append(act);
			} catch (const runtime_error& e) {
				actionErrors->append(e.what());
			}
		}
	}

	file.close();
	if (reader.hasError()) {
		throw runtime_error("Ошибка чтения: неверное содержание входного файла.");
	}
}
