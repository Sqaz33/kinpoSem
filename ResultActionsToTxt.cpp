#include "ResultActionsToTxt.h"

// реализовать в main, просто запись в main
ResultActionsToTxt::ResultActionsToTxt(const string& txtPath) {
	path = QString::fromStdString(txtPath);
}

void ResultActionsToTxt::writeResults(const QList<Result>& res) const {
	QFile file(path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		throw runtime_error("Ошибка записи: неверно указан путь выходного файла");
	}

	QTextStream out(&file);
	int i = 1;
	for (Result r : res) {
		QString o = "%1 %2 %3 %4 %5\n";
		o = o.arg(i++)
			.arg(QString::fromStdString(r.operation))
			.arg(QString::fromStdString(r.term1))
			.arg(QString::fromStdString(r.term2))
			.arg(QString::fromStdString(r.result));
		out << o;
	}

	file.close();
} 