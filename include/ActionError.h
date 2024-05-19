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
    OPERAND_LESS_ZERO_POW_FACT // Error performing
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
private:
    ActionErrorType e; /** @brief Error type. */
public:
    /**
     * @brief Constructor for ActionError.
     * @param[in] e Error type.
     */
    ActionError(ActionErrorType e) : e(e) {};

    /**
     * @brief Method to get the std::string representation of the error.
     * @return std::string representation of the error.
     */
    virtual std::string toStdString() const;
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
};

#endif // ACTION_ERROR_H