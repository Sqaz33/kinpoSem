#ifndef ACTION_FROM_XML_H
#define ACTION_FROM_XML_H

#include <string>
#include <stdexcept>

#include <QList>
#include <QXmlStreamReader>
#include <QFile>
#include <QHash>

#include "Action.h"

using namespace std;

/**
 * @brief Class for loading operations from an XML file.
*/
class ActionsFromXML {
public:
    /**
     * @brief ActionsFromXML constructor.
     * @param[in] XMLPath path to the XML file.
     * @param[out] actionErrors list of Action creation errors.
    */
    ActionsFromXML(const string& XMLPath, QList<ActionError>* actionErrors);

    /**
     * @brief ActionsFromXML destructor.
    */
    ~ActionsFromXML();

    /**
     * @brief Method to get the list of Actions.
     * @return List of Actions.
    */
    const QHash<int, Action*>* getActions() const;

private:
    QHash<int, Action*>* actions; /**@brief List of actions*/
    QList<ActionError>* actionErrors; /**@brief List of Action creation errors*/

    /**
     * @brief Method to load Actions from an XML file.
     * @param[in] XMLPath Path to the XML file.
     * 
     * @exception std::runtime_error if the file cannot be read.
     * @exception std::runtime_error if the XML file contents are incorrect.
    */
    void loadActions(const string& XMLPath);
};

#endif //ACTION_FROM_XML_H