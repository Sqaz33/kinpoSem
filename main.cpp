#include "iostream"

#include "BigRealNumber.h"
#include "Action.h"
#include "ActionsFromXML.h"
#include "StdStringsToTxt.h"
#include "locale"



int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru_RU.utf8");
	QList<runtime_error> actionErrors;
	try {
		//if (argc != 3) {
		//	throw runtime_error("Неверное количество аргументов ввода программы.");
		//}
		//string xmlPath(argv[1]);
		//string txtPath(argv[2]);

		Action act = Action::fromStdStrings("0", "-0.", "sdf");
		return 0;
	} catch (const runtime_error& e) {
		cout << e.what() << endl;
		puts(e.what());
		return 1;
	}
}
