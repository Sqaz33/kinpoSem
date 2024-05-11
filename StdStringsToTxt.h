#pragma once

#include "string"

#include "QList"
#include <QFile>
#include <QTextStream>

#include "Action.h"

/**
 * @brief ����� ��� ������ ����� � txt-�����.
*/
class StdStringToTxt {
public:
	/**
	 * @brief ����������� StdStringToTxt.
	 * @param[in] txtPath ���� �� txt-�����.
	*/
	StdStringToTxt(const string &txtPath);
	
	/**
	 * @brief ����� ������ ����� � txt-����.
	 * @param[in] strs ������ �����.
	 * @param[in] appendTo �������� �� � ����������� �����.
	 * 
	 * @exception std::runtime_error ���� �� ������� ������� �/��� ������� txt-����.
	*/
	void write(const QList<string>& strs, bool appendTo) const;

private:
	QString path; /**@brief ���� �� txt-����� �������*/
};

