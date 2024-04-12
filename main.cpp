#include "iostream"

#include "BigRealNumber.h"
#include "Action.h"
#include "ActionsFromXML.h"
#include "ResultActionsToTxt.h"
#include "locale"




QList<runtime_error> errors;
// сообщать обо всех ошибках во входных данных, если есть возмножсть получить к ним доступ.
// записать в файл в конце
int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru_RU.utf8");
	try {
		//if (argc != 3) {
		//	throw runtime_error("Неверное количество аргументов ввода программы.");
		//}
		//string xmlPath(argv[1]);
		//string txtPath(argv[2]);
		string xmlPath = "tksf.sdf";
		string txtPath = "";

		ActionsFromXML input(xmlPath);
		const QList<Action*>* actions = input.getActions();
		QList<Result> results;
		for (int i = 0; i < actions->length(); i++) {
			results.append(actions->at(i)->perform());
			if (results.last().isError) {
				results.last().result = results.last().result + " ��� ������� �" + to_string(i + 1);
				break;
			}
		}
		ResultActionsToTxt output(txtPath);
		output.writeResults(results);
		if (results.last().isError) {
			throw runtime_error(results.last().result);
		}
		return 0;
	} catch (const runtime_error& e) {
		string what(e.what());
		puts(e.what());
		return 1;
	}
}
