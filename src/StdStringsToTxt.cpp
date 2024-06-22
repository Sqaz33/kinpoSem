#include "../include/StdStringsToTxt.h"

StdStringToTxt::StdStringToTxt(const string& txtPath) {
	path = QString::fromStdString(txtPath);
}

void StdStringToTxt::write(const QList<string>& strs, bool appendTo) const {
	QFile file(path);
	QIODevice::OpenModeFlag of = appendTo ? QIODevice::Append : QIODevice::WriteOnly;
	if (!file.open(of | QIODevice::Text)) {
		throw runtime_error(
			"Execution error: it is not possible to open the txt file for writing."
			);
	}

	QTextStream out(&file);
	int i = 1;
	for (string s : strs) {
		QString str = QString::fromStdString(s) + "\n";
		out << str;
	}

	file.close();
} 