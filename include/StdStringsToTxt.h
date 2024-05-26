#ifndef STD_STRING_TO_TXT_H
#define STD_STRING_TO_TXT_H

#include <string>
#include <QList>
#include <QFile>
#include <QTextStream>

#include "Action.h"

/**
 * @brief Class for writing strings to txt files.
 */
class StdStringToTxt {
public:
    /**
     * @brief Constructor for StdStringToTxt.
     * @param[in] txtPath Path to the txt file.
     */
    StdStringToTxt(const std::string &txtPath);
    
    /**
     * @brief Method for writing strings to a txt file.
     * @param[in] strs List of strings.
     * @param[in] appendTo Whether to append to the file's content.
     * 
     * @exception std::runtime_error If unable to open and/or create the txt file.
     */
    void write(const QList<std::string>& strs, bool appendTo) const;

private:
    QString path; /** @brief Path to the txt file for answers */
};

#endif