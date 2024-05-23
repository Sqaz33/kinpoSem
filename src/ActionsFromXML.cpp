#include "../include/ActionsFromXML.h"

ActionsFromXML::ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors) {
	this->actionErrors = actionErrors;
	actions = new QHash<int, Action*>();
	loadActions(XMLPath);
}

ActionsFromXML::~ActionsFromXML() {
	delete actions;
}

const QHash<int, Action*>* ActionsFromXML::getActions() const {
	return actions;
}

void ActionsFromXML::loadActions(const string& XMLPath) {
	QString pt = QString::fromStdString(XMLPath);
	QFile file(pt);

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		throw runtime_error("execution error: unable to open the xml file for reading");
	}

	QXmlStreamReader reader(&file);

	int count = 1;
	while (!reader.atEnd() && !reader.hasError()) {

		BigRealNumber t1;
		BigRealNumber t2;
		int tCount = 0;
		Operation oper = NO_OPER;

		reader.readNext();
		if (reader.tokenType() == QXmlStreamReader::StartElement && reader.name() == "operation") {
			reader.readNext();
			bool isError = false;
			while (!(reader.tokenType() == QXmlStreamReader::EndElement && reader.name() == "operation")) {
				reader.readNext();
				string txt = reader.readElementText().toStdString();
				if (reader.name() == "operand1") {
					try {
						t1 = BigRealNumber::fromStdString(txt);
						tCount++;
					} catch (ActionBuildError& e) {
						isError = true;
						e.setXmlLineNumber(reader.lineNumber());
						actionErrors->append(e);
					}
				} else if (reader.name() == "operand2") {
					try {
						t2 = BigRealNumber::fromStdString(txt);
						tCount++;
					} catch (ActionBuildError& e) {
						isError = true;
						e.setXmlLineNumber(reader.lineNumber());
						actionErrors->append(e);
					}
				} else if (reader.name() == "operator") {
					oper = operFromStdString(txt);
					if (oper == NO_OPER) {
						isError = true;
						ActionBuildError e(NO_OPER_E);
						e.setXmlLineNumber(reader.lineNumber());
						actionErrors->append(e);
					}
				}
			}
			if (oper == NO_OPER) {
				isError = true;
				ActionBuildError e(NO_OPER_E);
				e.setXmlLineNumber(reader.lineNumber());
				actionErrors->append(e);
			}
			else if (tCount != 1 && tCount != 2) {
				isError = true;
				ActionBuildError e(INVALID_ARITY);
				e.setXmlLineNumber(reader.lineNumber());
				actionErrors->append(e);
			}

			if (!isError) {
				try {
					Action* a = tCount == 1 ? new Action(oper, &t1, nullptr) : new Action(oper, &t1, &t2);
					actions->insert(count++, a);
				} catch (ActionBuildError &e) {
					e.setXmlLineNumber(reader.lineNumber());
					actionErrors->append(e);
				}
			}
		}
	}

	file.close();
	if (reader.hasError()) {
		throw runtime_error("execution error: unable to read data from xml file");
	}
}
