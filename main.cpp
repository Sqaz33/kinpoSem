#include "iostream"

#include "BigRealNumber.h"
#include "Action.h"
#include "ActionsFromXML.h"
#include "StdStringsToTxt.h"

#include "locale"


int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru_RU.utf8");
	QList<ActionBuildError> actionBuildErrors;
	QList<ActionPerformError> actionPerformErrors;
	try {
		if (argc != 3) {
			throw runtime_error("Неверное количество аргументов ввода программы.");
		}
		string xmlPath(argv[1]);
		string txtPath(argv[2]);

		// получить действия
		ActionsFromXML input(xmlPath, &actionBuildErrors);
		const QHash<int, Action*>* actions = input.getActions();

		// произвести действия
		QList<string> results;
		QList<int> keys = actions->keys();
		qSort(keys.begin(), keys.end());
		for (int n : keys) {
			const Action* act = actions->value(n);
			try {
				string res = to_string(n)
							+ " "
							+ act->toStdString()
							+ " "
							+ act->perform().toStdString()
							+ "\n";
				results.append(res);
			} catch (const runtime_error& e) {
				string what = "error action #"
								+ to_string(n)
								+ " ------------------------\n"
								+ e.what()
								+ "\n"
								+ "---------------------------------";
				actionErrors.append(what);
			}
		}

		// вывести действия в файл
		StdStringToTxt output(txtPath);
		output.write(results, false);
		output.write(actionErrors, true);

		cout << "Ошибочных действий: " + to_string(actionErrors.size()) << endl;

		if (actionErrors.size()) {
			return 2;
		}

		return 0;
	} catch (const runtime_error& e) {
		puts(e.what());
		return 1;
	}
}
