//
// rational.hpp
// rational_number
//
// Created by Bryan Johnson on 10/16/14
//

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iostream>

class RationalNumber {
private:
    int numerator, denominator;
    void reduce(); 
    void formatRationalNumber();
    bool isValidFraction(std::string, std::string);
public:
    RationalNumber();
    RationalNumber(int);
    RationalNumber(int, int);
    RationalNumber(double); 
    RationalNumber(std::string);
    RationalNumber(const RationalNumber &);
    ~RationalNumber();
    
    bool operator< (const RationalNumber &);
    bool operator> (const RationalNumber &);
    bool operator== (const RationalNumber &);
    bool operator<= (const RationalNumber &);
    bool operator>= (const RationalNumber &);
    bool operator!= (const RationalNumber &);
    
    RationalNumber& operator= (const RationalNumber &);
    RationalNumber operator+ (const RationalNumber &);
    RationalNumber operator- (const RationalNumber &);
    RationalNumber operator* (const RationalNumber &);
    RationalNumber operator/ (const RationalNumber &);
    friend std::ostream& operator<<(std::ostream&, const RationalNumber&);
    
    void setDenominator(int);
    int getDenominator() const;
    void setNumerator(int);
    int getNumerator() const;
};

#endif
