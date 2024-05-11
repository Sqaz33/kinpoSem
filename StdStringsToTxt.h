#pragma once

#include "string"

#include "QList"
#include <QFile>
#include <QTextStream>

#include "Action.h"

/**
 * @brief Класс для записи строк в txt-файлы.
*/
class StdStringToTxt {
public:
	/**
	 * @brief Конструктор StdStringToTxt.
	 * @param[in] txtPath путь до txt-файла.
	*/
	StdStringToTxt(const string &txtPath);
	
	/**
	 * @brief Метод записи строк в txt-файл.
	 * @param[in] strs список строк.
	 * @param[in] appendTo добавить ли к содержимому файла.
	 * 
	 * @exception std::runtime_error если не удается открыть и/или создать txt-файл.
	*/
	void write(const QList<string>& strs, bool appendTo) const;

private:
	QString path; /**@brief Путь до txt-файла ответов*/
};

