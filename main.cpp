#include "iostream"

#include "BigRealNumber.h"
#include "Action.h"
#include "ActionsFromXML.h"
#include "StdStringsToTxt.h"

#include "locale"


/**
 * @brief Программа BigRealNumber предназначена для операций над 
 * рациональными числами, представленными в виде массива своих цифр.
 * @author Матвеев С.А. ПрИн-286 ФЭВТ
 * @param argc количество аргументов
 * @param argv[0] имя программы
 * @param argv[1] относительный или полный 
 *                путь до xml-файла с операциями 
 * @param argv[2] путь до txt-файла для вывода ответа
 * @return код завершения программы 
*/
int main(int argc, char* argv[]) {
	/*setlocale(LC_ALL, "ru_RU.utf8");*/
	QList<ActionError> actionErrors;
	try {
		if (argc != 3) {
			throw runtime_error("Неверное количество аргументов ввода программы.");
		}
		string xmlPath(argv[1]);
		string txtPath(argv[2]);

		// получить действия
		ActionsFromXML input(xmlPath, &actionErrors);
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
			} catch (ActionPerformError& e) {
				e.setActionNumber(n);
				actionErrors.append(e);
			}
		}

		QList<string> strErrors;
		for (ActionError e : actionErrors) {
			strErrors.append(e.toStdString());
		}
		// вывести действия в файл
		StdStringToTxt output(txtPath);
		output.write(results, false);
		output.write(strErrors, true);

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
