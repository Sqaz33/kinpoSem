#include "StdStringsToTxt.h"

// реализовать в main, просто запись в main
StdStringToTxt::StdStringToTxt(const string& txtPath) {
	path = QString::fromStdString(txtPath);
}

void StdStringToTxt::write(const QList<string>& strs) const {
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		throw runtime_error("Ошибка записи: неверно указан путь выходного файла");
	}

	QTextStream out(&file);
	int i = 1;
	for (string s : strs) {
		QString str = QString::fromStdString(s);
		out << str;
	}

	file.close();
} 