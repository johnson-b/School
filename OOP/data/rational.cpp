// 
// rational.cpp
// rational_number
// 
// Created by Bryan Johnson on 10/16/14
//
// This class implements a rational number using an int for the numerator and another int for the
// denominator.
//

#include "rational.hpp"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <math.h>
#include <stdlib.h>

/* 
 * Default constructor, results in a rational number that equates to zero. The numerator is 0
 * while the denominator is 1.
 */
RationalNumber::RationalNumber() {
    numerator = 0;
    denominator = 1;
}

/*
 * Constructor that takes one int. Results in a rational number where the numerator is the integer given
 * and the denominator is 1.
 */
RationalNumber::RationalNumber(int num) {
    numerator = num;
    denominator = 1;
}

/* 
 * Constructor that takes two ints. Results in a rational number where the numerator is the first integer
 * given and the denominator is the second integer given. There are checks along the way to insure the
 * numerator is always negative if only one negative integer is given (INVARIANT). Instead of creating a
 * separate function for this check, I decided to do this in the constructor that way the check is never needed
 * later on.
 */
RationalNumber::RationalNumber(int num, int den) {
    numerator = num;
    denominator = den;
    this->formatRationalNumber();
}

/*
 * Constructor that takes one double. Results in a rational number that is converted from double to a rational number by
 * doing the following: store value in a string, count digits after decimal place to use as denominator, remove decimal
 * and store as numerator. **DESIGN ALTERATION: Instead of creating a seperate function that alters an empty rational number,
 * using a double, I decided to elimnate a step and do it all in an overloaded constructor that takes in a double.
 */
RationalNumber::RationalNumber(double val) {
    std::string num = std::to_string(val);
    num.erase ( num.find_last_not_of('0') + 1, std::string::npos ); // Erase trailing zeros on double.
    unsigned decIndex = num.find(".");
    int digitCount = 0; // Keep track of digits after decimal place
    for(unsigned i = decIndex+1; i < num.length(); ++i) {
        digitCount++;
    }
    std::string den = "1";
    for(int j = 0; j < digitCount; ++j) { // Add a zero for each digit after decimal point.
        den += "0";
    }
    num = num.erase(decIndex, 1); // Erase decimal point and store as numerator.
    numerator = std::atoi(num.c_str());
    denominator = std::atoi(den.c_str());
    this->formatRationalNumber();
}

/*
 * Constructor that takes in a string. Parses string and results in a rational number where the numerator is the first
 * number before '/' and the denominator is the number after '/'. If the string is invalid, an invalid argument exception
 * is thrown. **DESIGN ALTERATION: Instead of creating a seperate function that alters an empty rational number by using,
 * a string, I decided to elimnate a step and do it all in an overloaded constructor that takes in a string.
 */
RationalNumber::RationalNumber(std::string str) {
    std::string num, den;
    std::size_t barIndex = str.find("/", 0);
    num = str.substr(0,barIndex);
    den = str.substr(barIndex+1);
    if(this->isValidFraction(num, den)) {
        numerator = std::atoi(num.c_str());
        denominator = std::atoi(den.c_str());
        this->formatRationalNumber();
    }
}

/*
 * Copy constructor that allows the copying of a rational number on creation. DESIGN ALTERATION: This was not pointed out
 * in the design interface, this can be very useful for the creation of rational number data structures.
 */
RationalNumber::RationalNumber(const RationalNumber &ratNum) {
    numerator = ratNum.numerator;
    denominator = ratNum.denominator;
    // No need to format ration number because the original rational number will have already been formatted correctly
}

/*
 * Deconstructor.
 */
RationalNumber::~RationalNumber() {};

/*
 * Find a common multiple of the denominator and multiply to the numerator for both rational numbers and compare.
 */
bool RationalNumber::operator< (const RationalNumber &ratNum) {
    RationalNumber tmp1 = *this, tmp2 = ratNum;
    int x = tmp1.numerator*tmp2.denominator;
    int y = tmp2.numerator*tmp1.denominator;
    
    return x < y;
}

/*
 * Find a common multiple of the denominator and multiply to the numerator for both rational numbers and compare.
 */
bool RationalNumber::operator> (const RationalNumber &ratNum) {
    RationalNumber tmp1 = *this, tmp2 = ratNum;
    int x = tmp1.numerator*tmp2.denominator;
    int y = tmp2.numerator*tmp1.denominator;
    
    return x > y;
}

/*
 * Find a common multiple of the denominator and multiply to the numerator for both rational numbers and compare.
 * DESIGN ALTERATION: Although the <= operator wasn't in the design interface, I decided it would be useful to along
 * with other operators.
 */
bool RationalNumber::operator<= (const RationalNumber &ratNum) {
    RationalNumber tmp1 = *this, tmp2 = ratNum;
    int x = tmp1.numerator*tmp2.denominator;
    int y = tmp2.numerator*tmp1.denominator;
    
    return x <= y;
}

/*
 * Find a common multiple of the denominator and multiply to the numerator for both rational numbers and compare.
 * DESIGN ALTERATION: Although the >= operator wasn't in the design interface, I decided it would be useful to along
 * with other operators.
 */
bool RationalNumber::operator>= (const RationalNumber &ratNum) {
    RationalNumber tmp1 = *this, tmp2 = ratNum;
    int x = tmp1.numerator*tmp2.denominator;
    int y = tmp2.numerator*tmp1.denominator;
    
    return x >= y;
}

/*
 * Find a common multiple of the denominator and multiply to the numerator for both rational numbers and compare.
 */
bool RationalNumber::operator==(const RationalNumber &ratNum) {
    if(this->numerator == ratNum.numerator) {
        return (this->denominator == ratNum.denominator);
    }
    return false;
}

/*
 * Find a common multiple of the denominator and multiply to the numerator for both rational numbers and compare.
 * DESIGN ALTERATION: Although the != operator wasn't in the design interface, I decided it would be useful to along
 * with other operators.
 */
bool RationalNumber::operator!=(const RationalNumber &ratNum) {
    if(this->numerator == ratNum.numerator) {
        if (this->denominator != ratNum.denominator)
            return true;
        else
            return false;
    }
    return true;
}

/*
 * Copy the members of left side rational number to members of right side rational number
 */
RationalNumber& RationalNumber::operator=(const RationalNumber &ratNum) {
    if (this == &ratNum)
        return *this;
    numerator = ratNum.numerator;
    denominator = ratNum.denominator;
    return *this;
}

/* 
 * Find the greatest common denominator and multiply both rational numbers. Add numerators and then reduce the
 * rational number.
 */
RationalNumber RationalNumber::operator+(const RationalNumber &ratNum) {
    RationalNumber tmp = *this;
    tmp.numerator = (tmp.numerator*ratNum.denominator)+(tmp.denominator*ratNum.numerator);
    tmp.denominator = tmp.denominator*ratNum.denominator;
    tmp.formatRationalNumber();
    return tmp;
}

/*
 * Find the greatest common denominator and multiply both rational numbers. Subtract numerators and then reduce the
 * rational number.
 */
RationalNumber RationalNumber::operator-(const RationalNumber &ratNum) {
    RationalNumber tmp = *this;
    tmp.numerator = (tmp.numerator*ratNum.denominator)-(tmp.denominator*ratNum.numerator);
    tmp.denominator = tmp.denominator*ratNum.denominator;
    tmp.formatRationalNumber();
    return tmp;
}

/*
 * Multiply both numerators and then both denominators of rational numbers. Then reduce.
 */
RationalNumber RationalNumber::operator*(const RationalNumber &ratNum) {
    RationalNumber tmp = *this;
    tmp.numerator = tmp.numerator*ratNum.numerator;
    tmp.denominator = tmp.denominator*ratNum.denominator;
    tmp.formatRationalNumber();
    return tmp;
}

/*
 * Find the reciprical of the right hand side and then multiple both numerators and both denominators. Then reduce.
 */
RationalNumber RationalNumber::operator/(const RationalNumber &ratNum) {
    RationalNumber tmp = *this;
    tmp.numerator = tmp.numerator*ratNum.denominator;
    tmp.denominator = tmp.denominator*ratNum.numerator;
    tmp.formatRationalNumber();
    return tmp;
}

/*
 * Overrides the << operator to use with ostream. Used to print out a rational number in the form of a fraction.
 * e.g. "1/2"
 */
std::ostream& operator<<(std::ostream &os, const RationalNumber &ratNum){
    os << ratNum.numerator << "/" << ratNum.denominator;
    return os;
}

/*
 * Reduces a rational number by finding the greatest common denominator and then dividing both the numerator and 
 * denominator of the fraction which then results in the same rational number, just reduced.
 */
void RationalNumber::reduce() {
    int x, y = denominator;
    x = numerator < 0 ? numerator * -1 : numerator; //Algorithm works when both integers are positive.
    
    while(x != y) {
        if(x > y)
            x -= y;
        else
            y -= x;
    }
    numerator /= x;
    denominator /=x;
}

/*
 * A simple function that first makes sure the rational number follows the invariants including no rational number
 * with a denominator of zero. Afterwards, it calls the reduce function to reduce each rational number. The function
 * is then called upon creation in each constructor. Throws invalid exception when denominator is zero.
 */
void RationalNumber::formatRationalNumber() {
    if(numerator < 0 && denominator < 0) { // If both integers are negative, the resulting rational number is positive.
        numerator *= -1;
        denominator *= -1;
        this->reduce();
    } else if(numerator == 0) { // If the numerator given is 0, the entire rational number is 0 so the denominator is reduced to 1.
        denominator = 1;
    } else if(denominator == 0) { // If a zero is given in the denominator, an invalid_argument exception is thrown.
        throw std::invalid_argument("Invalid Argument: Denominator of a rational number cannot be zero");
    } else if(numerator > 0 && denominator < 0) { // If denominator is negative, make numerator negative instead to follow invariant.
        numerator *= -1;
        denominator *= -1;
        this->reduce();
    } else {
        this->reduce();
    }
}

/*
 * When a rational number is created using a string, this parses the string to make sure that no invalid characters were
 * put into the string, if there are invalid characters present, an invalid argument exception is thrown. DESIGN ALERATION:
 * although this wasn't put into the design interface, instead of undefined behavior, I thought it would be more helpful
 * to give defined behavior. 
 */
bool RationalNumber::isValidFraction(std::string num, std::string den) {
    for (unsigned i = 0; i < num.length(); ++i) {
        if(!isdigit(num[i])) {
           throw std::invalid_argument("Invalid Argument: string is in incorrect format");
        }
    }
    for (unsigned j = 0; j < den.length(); ++j) {
        if (!isdigit(den[j])) {
            throw std::invalid_argument("Invalid Argument: string is in incorrect format");
        }
    }
    return true;
}

/*
 * Sets the denominator of a rational number using an int.
 */
void RationalNumber::setDenominator(int den) {
    if(den == 0)
        throw std::invalid_argument("Invalid Argument: Cannot set denominator to zero");
    denominator = den;
    this->formatRationalNumber();
}

/*
 * Returns denominator.
 */
int RationalNumber::getDenominator() const{
    return denominator;
}

/*
 * Sets the numerator of a rational number using an int.
 */
void RationalNumber::setNumerator(int num) {
    numerator = num;
    this->formatRationalNumber();
}

/*
 * Returns numerator.
 */
int RationalNumber::getNumerator() const{
    return numerator;
}













