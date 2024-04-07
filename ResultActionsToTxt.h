#pragma once

#include "string"

#include "QList"
#include <QFile>
#include <QTextStream>

#include "Action.h"


class ResultActionsToTxt {
private:
	QString path;
	
public:
	ResultActionsToTxt(const string &txtPath);
	
	void writeResults(const QList<Result>& res) const;
};

