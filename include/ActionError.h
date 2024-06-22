#ifndef ACTION_ERROR_H
#define ACTION_ERROR_H

#include <unordered_map>
#include <string>

/**
 * @brief Types of errors.
 */
enum ActionErrorType {
    NO_OPER_E, // Error creating object
    INVALID_ARITY, // Error creating object
    INVALID_OPERAND_FORMAT, // Error creating object
    INVALID_LENGTH, // Error creating or performing
    DIVISION_BY_ZERO, // Error performing
    OPERAND_WITH_FRACTIONAL_PART_POW_FACT, // Error performing
    OPERAND_LESS_ZERO_POW_FACT, // Error performing
    INTEGER_PART_OVERFLOW // Error performing 
};

/**
 * @brief Function to convert ActionErrorType to std::string.
 * @param[in] e ActionErrorType.
 * @return std::string representation of the error type.
 */
std::string errorTypeToStdString(ActionErrorType e);

/**
 * @brief Class representing an Action error.
 */
class ActionError {
protected:
    ActionErrorType e; /** @brief Error type. */
public:
    /**
     * @brief Constructor for ActionError.
     * @param[in] e Error type.
     */
    ActionError(ActionErrorType e) : e(e) {};

    //TODO: for tests only
    ActionError() : e(NO_OPER_E) {};

    /**
     * @brief Method to get the std::string representation of the error.
     * @return std::string representation of the error.
     */
    virtual std::string toStdString() const;

    virtual bool operator==(const ActionError &other) const;
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Derived class of ActionError.
 *        Class representing an Action creation error.
 */
class ActionBuildError : public ActionError {
private:
    int xmlLineNumber; /** @brief Line number in the XML file containing the erroneous action. */
public:
    /**
     * @brief Constructor for ActionBuildError.
     * @param[in] e Error type.
     */
    ActionBuildError(ActionErrorType e) : ActionError(e), xmlLineNumber(-1) {};
    //TODO: for tests only
    ActionBuildError() 
    : 
    xmlLineNumber(-1),
    ActionError()
    {};
    // TODO: добавить doxygen
    ActionBuildError(ActionBuildError *e) : ActionError(e->e), xmlLineNumber(e->xmlLineNumber) {};
    // TODO: добавить doxygen
    ActionErrorType type();

    /**
     * @brief Setter for the line number in the XML file containing the erroneous action.
     * @param[in] ln Line number in the XML file.
     */
    void setXmlLineNumber(int ln);

    /**
     * @brief Method to get the std::string representation of the error.
     * @return std::string representation of the error.
     */
    std::string toStdString() const override;

    bool operator==(const ActionError &other) const override;

    ActionBuildError& operator=(const ActionBuildError &other);
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Derived class of ActionError.
 *        Class representing an Action performance error.
 */
class ActionPerformError : public ActionError {
private:
    int actionNumber; /** @brief Number of the Action object that caused the error. */
public:
    /**
     * @brief Constructor for ActionPerformError.
     * @param[in] e Error type.
     */
    ActionPerformError(ActionErrorType e) : ActionError(e), actionNumber(-1) {};
    
    //TODO: for tests only
    ActionPerformError()
    :
    actionNumber(-1),
    ActionError()
    {};
    
    // TODO: добавить doxygen
    ActionPerformError(ActionPerformError *e) : ActionError(e->e), actionNumber(e->actionNumber) {};
    // TODO: добавить doxygen
     ActionErrorType type();

    /**
     * @brief Method to get the std::string representation of the error.
     * @return std::string representation of the error.
     */
    std::string toStdString() const override;

    /**
     * @brief Setter for the number of the Action object that caused the error.
     * @param[in] a Number of the Action object.
     */
    void setActionNumber(int a);

    bool operator==(const ActionError &other) const override;
};

#endif // ACTION_ERROR_H