#ifndef BIG_REAL_NUMBER_H
#define BIG_REAL_NUMBER_H

#include <qregexp>
#include <QString>

#include <string>
#include <stdexcept>
#include <iostream>
#include "math.h"

#include "ActionError.h"

#define MAX_LENGTH 1000

using namespace std;

/**
 * @brief Class for representing real numbers as arrays of their digits.
 * Subsequently referred to as BigRealNumber - BRN.
*/
class BigRealNumber {
     
private:
   //   TODO:  Access to internal fields for testing purposes
    short* intPrt; /**@brief Array representing the integer part.*/
    short* fractPrt; /**@brief Array representing the fractional part.*/

    int intPrtLen; /**@brief Length of the integer part.*/
    int fractPrtLen; /**@brief Length of the fractional part.*/
    bool isNegative; /**@brief Flag indicating whether the number is negative.*/
    // 
public:
    // TODO:  Access to internal fields for testing purposes
    //=====================================================
    const short* getIntPrt() const { return intPrt; }
    const short* getFractPrt() const { return fractPrt; }
    //=====================================================
    
    /**
     * @brief Copy constructor.
     * @param[in] p BRN object being copied.
    */
    BigRealNumber(const BigRealNumber& p);

    /**
     * @brief Constructor from an integer.
     * @param[in] n Integer number. 
    */
    BigRealNumber(int n);

    /**
     * @brief Constructor for an "empty" object.
    */
    BigRealNumber();

    /**
     * @brief Destructor for BRN.
    */
    ~BigRealNumber();

    /**
     * @brief Method to generate a BRN from a string representation of a real number.
     * @param[in] numb String representation of the number:
     * 
     * @pre
     * Requirements for numb.
     * numb must have the form "sign[integer_part]separator[fractional_part]".
     * 
     * Sign: number is negative -> numb[0] == '-', number is positive -> numb[0] - digit of the integer part.
     * 
     * Integer_part: max(length) = 1000, min(length) - 1. 
     * 
     * Separator: '.' character.
     * 
     * Fractional_part: max(length) = 1000, min(length) - 1. 
     * 
     * Fractional and integer parts should only contain digit characters (0-9).
     * 
     * numb - should only contain the following characters: digits {'-', ('0'-'9'), '.',}
     * 
     * @return BRN object.
     * 
     * @exception ActionBuildError if the string representation numb of the number does not meet the requirements.
    */
    static BigRealNumber fromStdString(const string& numb);

    /**
     * @brief Method to validate a std::string representation of a number,
     * indicating whether a BRN object can be created from this string.
     * 
     * @param[in] numb String representation of the number.
     * @return Whether a BRN object can be created from this std::string.
    */
    static bool validateStdString(const string& numb);
    /**
     * @brief Method to validate a QString representation of a number,
     * indicating whether a BRN object can be created from this string.
     *
     * For example: "-5.0", "0.3".
     *
     * @param[in] numb String representation of the number.
     * @return Whether a BRN object can be created from this QString.
    */
    static bool validateQString(const QString& numb);


    /**
     * @brief Method to get the length of the integer part of the number.
     * @return Length of the integer part of the number.
    */
    int getIntPrtLen() const;
    /**
     * @brief Method to get the length of the fractional part of the number.
     * @return Length of the integer part of the number.
    */
    int getFractPrtLen() const;

    /**
     * @brief Method to get the sign of the number.
     * @return Sign of the number.
    */
    bool negative() const;


    /**
     * @brief Method to convert to a std::string representation of the number.
     * @return std::string representation of the number.
    */
    string toStdString() const;

    /**
     * @brief Overloaded assignment operator (=).
     * @param[in] other BRN object.
     * @return New BRN object.
    */
    BigRealNumber& operator=(const BigRealNumber &other);
    /**
     * @brief Overloaded assignment operator (=) for boolean value.
     * @param[in] bl Boolean value.
     * @return New BRN object.
    */
    BigRealNumber& operator=(bool bl);

    /**
     * @brief Overloaded addition operator (+).
     * @param[in] other Second addend.
     * @return Sum result.
    */
    BigRealNumber operator+(const BigRealNumber &other) const;
    /**
     * @brief Overloaded addition operator (+).
     * @param[in] other Second addend.
     * @return Sum result.
    */
    BigRealNumber operator+(int other) const;

    /**
     * @brief Overloaded subtraction operator (-).
     * @param[in] other Subtrahend.
     * @return Subtraction result.
    */
    BigRealNumber operator-(const BigRealNumber &other) const;
    /**
     * @brief Overloaded subtraction operator (-).
     * @param[in] other Subtrahend.
     * @return Subtraction result.
    */
    BigRealNumber operator-(int n) const;

    /**
     * @brief Overloaded multiplication operator (*).
     * @param[in] other Multiplier.
     * @return Multiplication result.
    */
    BigRealNumber operator*(const BigRealNumber &other) const;
    /**
     * @brief Overloaded multiplication operator (*).
     * @param[in] other Multiplier.
     * @return Multiplication result.
    */
    BigRealNumber operator*(int n) const;

    /**
     * @brief Overloaded division operator (/).
     * @param[in] other Divisor.
     * @return Division result.
    */
    BigRealNumber operator/(const BigRealNumber &other) const;
    /**
     * @brief Overloaded division operator (/).
     * @param[in] other Divisor.
     * @return Division result.
    */
    BigRealNumber operator/(int n) const;

    /**
     * @brief Overloaded equality operator (==).
     * @param[in] other BRN object to compare.
     * @return Whether the numbers are equal.
    */
    bool operator==(const BigRealNumber &other) const;
    /**
     * @brief Overloaded equality operator (==).
     * @param[in] other Number to compare.
     * @return Whether the numbers are equal.
    */
    bool operator==(int other) const;

    /**
     * @brief Overloaded inequality operator (!=).
     * @param other BRN object to compare.
     * @return Whether the numbers are not equal. 
    */
    bool operator!=(const BigRealNumber &other) const;
    /**
     * @brief Overloaded inequality operator (!=).
     * @param[in] other Number to compare.
     * @return Whether the numbers are not equal.
    */
    bool operator!=(int other) const;

    /**
     * @brief Overloaded less than
    * operator (<).
     * @param[in] other BRN object to compare.
     * @return Whether this number is less than the other.
    */
    bool operator<(const BigRealNumber &other) const;

    /**
     * @brief Overloaded greater than operator (>).
     * @param[in] other BRN object to compare.
     * @return Whether this number is greater than the other.
    */
    bool operator>(const BigRealNumber &other) const;
    /**
     * @brief Overloaded greater than operator (>).
     * @param[in] other Number to compare.
     * @return Whether this number is greater than the other.
    */
    bool operator>(int other) const;

    /**
     * @brief Overloaded less than or equal to operator (<=).
     * @param[in] other BRN object to compare.
     * @return Whether this number is less than or equal to the other.
    */
    bool operator<=(const BigRealNumber &other) const;

    /**
     * @brief Overloaded greater than or equal to operator (>=).
     * @param[in] other BRN object to compare.
     * @return Whether this number is greater than or equal to the other.
    */
    bool operator>=(const BigRealNumber &other) const;

    /**
     * @brief Method for exponentiation.
     * @param[in] pw Power. 
     * @return Result of exponentiation.
     * 
     * @pre The method raises only to non-negative integer power.
     * @pre pw > 0 && !pw.fractPrt.
     * 
     * @exception ActionPerformError if the power is negative.
     * @exception ActionPerformError if the power is not an integer.
    */
    BigRealNumber pow(BigRealNumber pw) const;

    /**
     * @brief Method for calculating factorial.
     * @return Result of factorial calculation.
     *
     * @pre The method calculates factorial only for non-negative integer numbers. 
     * @pre this > 0 && !this.fractPrt.
     *
     * @exception ActionPerformError if the number is negative.
     * @exception ActionPerformError if the number is not an integer.
    */
    BigRealNumber factorial() const;

private:
   // TODO:  short* intPrt; /**@brief Array representing the integer part.*/
    // short* fractPrt; /**@brief Array representing the fractional part.*/

    // int intPrtLen; /**@brief Length of the integer part.*/
    // int fractPrtLen; /**@brief Length of the fractional part.*/
    // bool isNegative; /**@brief Flag indicating whether the number is negative.*/

    /**
     * @brief Internal addition method, 
     *        equivalent to the operator+ method 
     *        in the public interface.
     * @see operator+
     * @param[in] term2 
     * @param[out] res 
    */
    void add(
        const BigRealNumber& term2,
        BigRealNumber& res
    ) const;

    /**
     * @brief Internal subtraction method,
     *        equivalent to the operator- 
     *        method in the public interface.
     * @see operator-
     * @param[in] term2
     * @param[out] res
    */
    void sub(
        const BigRealNumber& subtr,
        BigRealNumber& res
    ) const;

    /**
     * @brief Internal multiplication method,
     *        equivalent to the operator*
     *        method in the public interface.
     * @see operator*
     * @param[in] term2
     * @param[out] res
    */
    void mul(
        const BigRealNumber& fac,
        BigRealNumber& res
    ) const;
    
    /**
     * @brief Internal division method,
     *        equivalent to the operator/
     *        method in the public interface
     * @see operator/
     * @param[in] term2
     * @param[out] res
    */
    void div(
        const BigRealNumber& diver,
        BigRealNumber& res
    ) const;

 /**
     * @brief Method for division with remainder.
     * @param[in] diver Divisor.
     * @param[out] R Division result. 
     * @param[out] Q Remainder.
    */
    void divRemaind(
        const BigRealNumber& diver,
        BigRealNumber& R,
        BigRealNumber& Q
    ) const;

    /**
     * @brief Method for "applying" arrays.
     *        During "application", subtraction or addition of arrays occurs.
     * @param[in] term1 First operand.
     * @param[in] term2 Second operand.
     * @param[out] res Result of the action.
     * @param[in] addToFract Whether to work with fractional parts.
     * @param[in] minusTerm2 Whether to subtract.
     * @param[in] transfer Carry.
     * @return Carry.
    */
    short attachArrays(
        const BigRealNumber& term1,
        const BigRealNumber& term2,
        BigRealNumber& res,
        bool addToFract,
        bool minusTerm2,
        short transfer
    ) const;

    /**
     * @brief Method for adding a value to the end of the integer part.
     * @param[in] number Value to be added.
     * 
     * @exception ActionPerformError if overflow of the integer part occurs.
    */
    void appendToInt(short number);
    
    /**
     * @brief Method for adding a value to the fractional part at the index.
     * @param[in] number Value to be added.
     * @param[in] ind Index at which the number is added.
     * @return Whether the addition was successful.
    */
    bool appendToFract(short number, int ind);

    /**
     * @brief Method for removing insignificant digits.
    */
    void removeInsignDigits();

    /**
     * @brief Method for shifting the entire number.
     * 
     * For example:
     * 32.2 >> 1 --> 3.22
     * 
     * @param[in] shift How many digits to shift.
     * @param[in] toRight Direction flag of the shift.
    */
    void shiftNumber(int shift, bool toRight);

    /**
     * @brief Method for setting an integer value.
     * @param[in] n Integer value.
    */
    void setVal(int n);
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Method for shifting an array.
 * @param[in] arr Array.
 * @param[in] len Length of the array.
 * @param[in] shift Shift.
 * @param[in] toRight Direction flag of the shift.
 * @param[in] fillVal Value for filling.
*/
void arrShift(short* arr, int len, int shift, bool toRight, int fillVal);

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Method for getting the index of the first non-zero value.
 * @param[in] arr Array.
 * @param[in] start Start of pointer movement.
 * @param[in] stop End of pointer movement.
 * @param[in] backward Direction flag of pointer movement.
 * @return Index of the first non-zero value. 
*/
int getFirstNotZero(short* arr, int start, int stop, bool backward);

#endif // BIG_REAL_NUMBER_H