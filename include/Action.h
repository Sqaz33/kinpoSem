#pragma once

#include <unordered_map>
#include <string>
#include <sstream>
#include <QString>

#include "BigRealNumber.h"
#include "ActionError.h"

//----------------------Operation Handling----------------------------

/**
 * @brief List of operations
*/
enum Operation {
    ADD,
    SUBT,
    MUL,
    DIV,
    POW,
    FACT,
    EQUALS,
    NOT_EQUALS,
    LESS,
    NO_MORE,
    MORE,
    NO_LESS,
    NO_OPER
};

/**
 * @relates Operation
 *
 * @brief Function to get the enumerated operation from its string representation.
 * @param[in] oper string representation of the operation.
 * 
 * @return Operation from the Operation enumeration.
 * 
 * @remark The function will return Operation::NO_OPER if there is no corresponding string representation.
 *
*/
Operation operFromStdString(const std::string& oper);

/**
 * @relates Operation
 *
 * @brief Function to get the string representation of the operation from the Operation enumeration.
 * @param[in] oper operation from the Operation enumeration.
 * @return String representation of the operation.
*/
std::string stdStringFromOper(Operation oper);
//--------------------------------------------------------------------------

/**
 * @brief Class to represent an action.
 *
 * @sa
 * ---------------
 * Example of an action:
 * 1 + 2 = 3
 * term1 = 1
 * term2 = 2
 * oper = '+'
 * perform - '='
 * 3 - perform return
 * --------------------
 *
*/
class Action {
public:
    /**
     * @brief Action constructor.
     * @param[in] oper string representation of the operation.
     * @param[in] term1 string representation of the first operand.
     * @param[in] term2 string representation of the second operand.
     * 
     * @exception ActionBuildError if the number of operands is incorrect.
    */
    Action(Operation oper, const BigRealNumber* term1, const BigRealNumber* term2);

    /**
     * @brief Method to perform the action.
     * @return Result of the action.
    */
    BigRealNumber perform() const;

    /**
     * @brief Function to get the string representation of the action.
     * @return String representation of the action.
    */
    std::string toStdString() const;

private:
    BigRealNumber term1; /**@brief First operand.*/
    BigRealNumber term2; /**@brief Second operand.*/
    Operation oper; /**@brief Operation.*/
    int termCount;  /**@brief Number of operands*/

    /**
     * @brief Function to check the arity of the action.
     * @return Whether the arity of the action is correct.
    */
    bool checkArity();
};
