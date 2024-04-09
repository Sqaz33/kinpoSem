#include "iostream"

#include "BigRealNumber.h"
#include "Action.h"
#include "ActionsFromXML.h"
#include "ResultActionsToTxt.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		throw runtime_error("Incorrect number of program input arguments.");
	}
	string xmlPath(argv[1]);
	string txtPath(argv[2]);

	try {
		ActionsFromXML input(xmlPath);
		const QList<Action*>* actions = input.getActions();
		QList<Result> results;
		for (int i = 0; i < actions->length(); i++) {
			results.append(actions->at(i)->perform());
			if (results.last().isError) {
				results.last().result = results.last().result + " для расчета №" + (char) ('0' + i + 1);
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
		cout << e.what();
		return 1;
	}
}
