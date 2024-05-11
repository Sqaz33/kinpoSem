#pragma once

#include "string"
#include "stdexcept"

#include "qlist"
#include "qXmlStreamReader"
#include "qFile"
#include "qhash"

#include "Action.h"
using namespace std;


/**
 * @brief Класс для загрузки операций из xml-файла.
*/
class ActionsFromXML {
public:
	/**
	 * @brief Конструктор ActionsFromXML.
	 * @param[in] XMLPath путь до xml-файла.
	 * @param[out] actionErrors список ошибок создания Action.
	*/
	ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors);

	/**
	 * @brief Деструктор ActionsFromXML;
	*/
	~ActionsFromXML();

	/**
	 * @brief Метод для получения списка Action.
	 * @return Список Aciton.
	*/
	const QHash<int, Action*>* getActions() const;

private:
	QHash<int, Action*>* actions; 	/**@brief Список действий*/
	QList<ActionError>* actionErrors;	/**@brief Список ошибок создания Action*/

	/**
	 * @brief Метод для загрузки Action из xml-файла. 
	 * @param[in] XMLPath Путь до xml-файла
	 * 
	 * @exception std::runtime_error если невозможно прочесть файл.
	 * @exception std::runtime_error если неверное содержание xml-файла.
	*/
	void loadActions(const string& XMLPath);
};

