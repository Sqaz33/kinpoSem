#include "ActionsFromXML.h"

ActionsFromXML::ActionsFromXML(const string& XMLPath, QList<string>* actionErrors) {
	this->actionErrors = actionErrors;
	actions = QHash<int, Action*>();
	loadActions(XMLPath);
}

const QHash<int, Action*>* ActionsFromXML::getActions() const {
	return &actions;
}

void ActionsFromXML::loadActions(const string& XMLPath) {
	QString pt = QString::fromStdString(XMLPath);
	QFile file(pt);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw runtime_error("������ ������: ������� ������ ���� ��������� �����");
	}

	QXmlStreamReader reader(&file);
	string term1;
	string term2;
	string oper;

	int count = 1;
	while (!reader.atEnd() && !reader.hasError()) {
		reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "operation") {
			reader.readNext();
			term2 = "NaN";
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
		}
		try {
			actions[count++] = Action::fromStdStrings(
				oper, term1, term2
			);
		}
		catch (const runtime_error& e) {
			string what = "for action #"
				+ to_string(count++)
				+ " ------------------------\n"
				+ e.what()
				+ "\n"
				+ "---------------------------------";
			actionErrors->append(e.what());
		}
	}

	file.close();
	if (reader.hasError()) {
		throw runtime_error("������ ������: �������� ���������� �������� �����.");
	}
}
