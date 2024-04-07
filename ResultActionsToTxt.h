#pragma once

#include "string"
#include "QList"

#include "Action.h"


class ResultActionsToTxt {
private:
	string path;
	
public:
	ResultActionsToTxt(const string &txtPath);
	
	void writeResults(const QList<Result>& res) const;
};

