#pragma once

#include "string"

#include "QList"
#include <QFile>
#include <QTextStream>

#include "Action.h"


class StdStringToTxt {
private:
	QString path;
	
public:
	StdStringToTxt(const string &txtPath);
	
	void write(const QList<string>& strs, bool appendTo) const;
};

