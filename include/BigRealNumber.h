#pragma once

#include "qregexp"
#include "QString"

#include <string>
#include <stdexcept>
#include "math.h"

#include <vector>
#include <memory>

#include "ActionError.h"

using namespace std;

/**
 * @brief Class for representing real numbers as an array of their digits.
 * Further, BigRealNumber - BRN.
*/
class BigRealNumber {
public:
    /**
     * @brief Copy constructor.
     * @param[in] p the BRN object to be copied.
    */
    BigRealNumber(const BigRealNumber& p);

    /**
     * @brief Constructor from an integer.
     * @param[in] n an integer number.
    */
    BigRealNumber(int n);

    /**
     * @brief Default constructor.
    */
    BigRealNumber();

    /**
     * @brief Destructor of BRN.
    */
    ~BigRealNumber();

    /**
     * @brief Method for creating a BRN from a string representation of a real number.
     * @param[in] numb string representation of the number:
     * 
     * @pre
     * Requirements for numb.
     * numb should be in the format "sign[integer_part]separator_symbol[fractional_part]".
     * 
     * Sign: number is negative -> numb[0] == '-', number is positive -> numb[0] is a digit of the integer part.
     * 
     * Integer_part: max(length) = 1000, min(length) = 1. 
     * 
     * Separator_symbol: '.' (dot).
     * 
     * Fractional_part: max(length) = 1000, min(length) = 1. 
     * 
     * The integer and fractional parts should only contain digit characters (0-9).
     * 
     * numb should contain only the following characters: digits {'-', ('0'-'9'), '.',}
     * 
     * @return BRN object.
     * 
     * @exception ActionBuildError if the string representation numb does not meet the requirements.
    */
    static BigRealNumber fromStdString(const string& numb);

    /**
     * @brief Method for validating std::string representation of a number,
     * indicating whether it is possible to create a BRN object from this string.
     * 
     * @param[in] numb string representation of the number.
     * @return Whether it is possible to create a BRN object from this std::string.
    */
    static bool validateStdString(const string& numb);
    
    /**
     * @brief Method for validating QString representation of a number,
     * indicating whether it is possible to create a BRN object from this string.
     *
     * Example: "-5.0", "0.3".
     *
     * @param[in] numb string representation of the number.
     * @return Whether it is possible to create a BRN object from this QString.
    */
    static bool validateQString(const QString& numb);


    /**
     * @brief Method to get the length of the integer part of the number.
     * @return Length of the integer part of the number.
    */
    int getIntPrtLen() const;
    
    /**
     * @brief Method to get the length of the fractional part of the number.
     * @return Length of the fractional part of the number.
    */
    int getFractPrtLen() const;


    /**
     * @brief Method to convert to std::string representation of the number.
     * @return std::string representation of the number.
    */
    string toStdString() const;

    /**
     * @brief Assignment operator overload (=).
     * @param[in] other BRN object.
     * @return New BRN object.
    */
    BigRealNumber& operator=(const BigRealNumber &other);
    
    /**
     * @brief Assignment operator overload (=) from a boolean value.
     * @param[in] bl boolean value.
     * @return New BRN object.
    */
    BigRealNumber& operator=(bool bl);

    /**
     * @brief Addition operator overload (+).
     * @param[in] other the second addend.
     * @return Result of the addition.
    */
    BigRealNumber operator+(const BigRealNumber &other) const;
    
    /**
     * @brief Addition operator overload (+).
     * @param[in] other the second addend.
     * @return Result of the addition.
    */
    BigRealNumber operator+(int other) const;

    /**
     * @brief Subtraction operator overload (-).
     * @param[in] other the subtrahend.
     * @return Result of the subtraction.
    */
    BigRealNumber operator-(const BigRealNumber &other) const;
    
    /**
     * @brief Subtraction operator overload (-).
     * @param[in] other the subtrahend.
     * @return Result of the subtraction.
    */
    BigRealNumber operator-(int n) const;

    /**
     * @brief Multiplication operator overload (*).
     * @param[in] other the multiplier.
     * @return Result of the multiplication.
    */
    BigRealNumber operator*(const BigRealNumber &other) const;
    
    /**
     * @brief Multiplication operator overload (*).
     * @param[in] other the multiplier.
     * @return Result of the multiplication.
    */
    BigRealNumber operator*(int n) const;

    /**
     * @brief Division operator overload (/).
     * @param[in] other the divisor.
     * @return Result of the division.
    */
    BigRealNumber operator/(const BigRealNumber &other) const;
    
    /**
     * @brief Division operator overload (/).
     * @param[in] other the divisor.
     * @return Result of the division.
    */
    BigRealNumber operator/(int n) const;

    /**
     * @brief Equality operator overload (==).
     * @param[in] other BRN object to compare.
     * @return Whether the numbers are equal.
    */
    bool operator==(const BigRealNumber &other) const;
    
    /**
     * @brief Equality operator overload (==).
     * @param[in] other number to compare.
     * @return Whether the numbers are equal.
    */
    bool operator==(int other) const;

    /**
     * @brief Inequality operator overload (!=).
     * @param other BRN object to compare.
     * @return Whether the numbers are not equal.
    */
    bool operator!=(const BigRealNumber &other) const;
    
    /**
     * @brief Inequality operator overload (!=).
     * @param[in] other number to compare.
     * @return Whether the numbers are not equal.
    */
    bool operator!=(int other) const;

    /**
     * @brief Less than operator overload (<).
     * @param[in] other BRN object to compare.
     * @return Whether this number is less than the other.
    */
    bool operator<(const BigRealNumber &other) const;

    /**
     * @brief Greater than operator overload (>).
     * @param[in] other BRN object to compare.
     * @return Whether this number is greater than the other.
    */
    bool operator>(const BigRealNumber &other) const;
    
    /**
     * @brief Greater than operator overload (>).
     * @param[in] other number to compare.
     * @return Whether this number is greater than the other.
    */
    bool operator>(int other) const;

    /**
     * @brief Less than or equal to operator overload (<=).
     * @param[in] other BRN object to compare.
     * @return Whether this number is less than or equal to the other.
    */
    bool operator<=(const BigRealNumber &other) const;

    /**
     * @brief Greater than or equal to operator overload (>=).
     * @param[in] other BRN object to compare.
     * @return Whether this number is greater than or equal to the other.
    */
    bool operator>=(const BigRealNumber &other) const;

    /**
     * @brief Method for exponentiation.
     * @param[in] pw exponent.
     * @return Result of exponentiation.
     * 
     * @pre The method only raises to a non-negative integer power.
     * @pre pw > 0 && !pw.fractPrt.
     * 
     * @exception ActionPerformError if the exponent is negative.
     * @exception ActionPerformError if the exponent is not an integer.
    */
    BigRealNumber pow(BigRealNumber pw) const;

    /**
     * @brief Method for calculating the factorial.
     * @return Result of the factorial calculation.
     *
     * @pre The method only calculates the factorial for non-negative integer numbers. 
     * @pre this > 0 && !this.fractPrt.
     *
     * @exception ActionPerformError if the number is negative.
     * @exception ActionPerformError if the number is not an integer.
    */
    BigRealNumber factorial() const;

private:

    bool isNegative; /**@brief Flag indicating whether this number is negative.*/

    /**
     * @brief Internal addition method,
     *        analogous to the operator+ method
     *        from the public interface.
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
     *        analogous to the operator- method
     *        from the public interface.
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
     *        analogous to the operator* method
     *        from the public interface.
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
     *        analogous to the operator/ method
     *        from the public interface
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
     * @param[in] diver divisor.
     * @param[out] R result of the division. 
     * @param[out] Q remainder of the division.
    */
    void divRemaind(
        const BigRealNumber& diver,
        BigRealNumber& R,
        BigRealNumber& Q
    ) const;

    /**
     * @brief Method for "attaching" arrays
     *        During the "attachment", the arrays are either added or subtracted.
     * @param[in] term1 first operand.
     * @param[in] term2 second operand.
     * @param[out] res result of the operation.
     * @param[in] addToFract whether to work with fractional parts.
     * @param[in] minusTerm2 whether to subtract.
     * @param[in] transfer carry-over.
     * @return Carry-over.
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
     * @brief Method to add a value to the end of the integer part.
     * @param[in] number the number to add.
     * 
     * @exception ActionPerformError if there is an overflow of the integer part.
    */
    void appendToInt(short number);
    
    /**
     * @brief Method to add a value to the fractional part at a specific index.
     * @param[in] number the number to add.
     * @param[in] ind index at which to add the number.
     * @return Whether the addition was successful.
    */
    bool appendToFract(short number, int ind);

    /**
     * @brief Method to remove insignificant digits.
    */
    void removeInsignDigits();

    /**
     * @brief Method to shift the entire number.
     * 
     * For example:
     * 32.2 >> 1 --> 3.22
     * 
     * @param[in] shift the number of digits to shift.
     * @param[in] toRight flag indicating the direction of the shift.
    */
    void shiftNumber(int shift, bool toRight);

    /**
     * @brief Method to set an integer value.
     * @param[in] n integer value.
    */
    void setVal(int n);
};

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Method to shift an array.
 * @param[in] arr array.
 * @param[in] len length of the array.
 * @param[in] shift shift amount.
 * @param[in] toRight flag indicating the direction of the shift.
 * @param[in] fillVal value for filling.
*/
template <typename T>
void arrShift(T* arr, int len, int shift, bool toRight, T fillVal);

/**
 * @see BigRealNumber
 * @relates BigRealNumber
 * @brief Method to get the index of the first non-zero value.
 * @param[in] arr array.
 * @param[in] start start of the pointer movement.
 * @param[in] stop end of the pointer movement.
 * @param[in] backward flag indicating the direction of pointer movement.
 * @return index of the first non-zero value.
*/
int getFirstNotZero(short* arr, int start, int stop, bool backward);
