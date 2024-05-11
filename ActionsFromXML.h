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
 * @brief ����� ��� �������� �������� �� xml-�����.
*/
class ActionsFromXML {
public:
	/**
	 * @brief ����������� ActionsFromXML.
	 * @param[in] XMLPath ���� �� xml-�����.
	 * @param[out] actionErrors ������ ������ �������� Action.
	*/
	ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors);

	/**
	 * @brief ���������� ActionsFromXML;
	*/
	~ActionsFromXML();

	/**
	 * @brief ����� ��� ��������� ������ Action.
	 * @return ������ Aciton.
	*/
	const QHash<int, Action*>* getActions() const;

private:
	QHash<int, Action*>* actions; 	/**@brief ������ ��������*/
	QList<ActionError>* actionErrors;	/**@brief ������ ������ �������� Action*/

	/**
	 * @brief ����� ��� �������� Action �� xml-�����. 
	 * @param[in] XMLPath ���� �� xml-�����
	 * 
	 * @exception std::runtime_error ���� ���������� �������� ����.
	 * @exception std::runtime_error ���� �������� ���������� xml-�����.
	*/
	void loadActions(const string& XMLPath);
};

