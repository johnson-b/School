// 
// main.cpp
// rational_number
//
// Created by Bryan Johnson on 10/16/14
//

#include "rational.hpp"
#include <iostream>
#include <cassert>
#include <stdexcept>

int main() {
    RationalNumber rn1("1/2");
    RationalNumber rn2(2, 3);
    RationalNumber rn3(.75);
    
    std::cout << "---- '<<' Operator ----" << std::endl;
    std::cout << "Rn1 = " << rn1 << std::endl;
    std::cout << "Rn2 = " << rn2 << std::endl;
    std::cout << "Rn3 = " << rn3 << std::endl;
    
    std::cout << "---- Mathematical Operators ----" << std::endl;
    std::cout << "Rn1 + Rn2 = " << rn1 + rn2 << std::endl;
    std::cout << "Rn2 - Rn3 = " << rn2 - rn3 << std::endl;
    std::cout << "Rn3 * Rn1 = " << rn3 * rn1 << std::endl;
    std::cout << "Rn2 / Rn3 = " << rn2 / rn3 << std::endl;
    
    std::cout << "---- Comparison Operators ----" << std::endl;
    std::cout << "Rn1 < Rn2 is: ";
    if(rn1 < rn2)
        std::cout << "true" << std::endl;
    std::cout << "Rn3 > Rn1 is: ";
    if(rn3 > rn1)
        std::cout << "true" << std::endl;
    std::cout << "Rn1 <= Rn2 is: ";
    if(rn1 <= rn2)
        std::cout << "true" << std::endl;
    std::cout << "Rn3 > Rn2 is: ";
    if(rn3 >= rn2)
        std::cout << "true" << std::endl;
    std::cout << "Rn1 != Rn2 is: ";
    if(rn1 != rn2)
        std::cout << "true" << std::endl;
    std::cout << "Rn1 == Rn2 is: ";
    if(!(rn1 == rn2))
        std::cout << "false" << std::endl;
    
    std::cout << "---- Altering Fraction on the fly using Accsessors/Modifiers ----" << std::endl;
    std::cout << "rn3.setDenominator(16);" << std::endl; rn3.setDenominator(16);
    std::cout << "rn3.setNumerator(4);" << std::endl; rn3.setNumerator(4);
    std::cout << "Rn3's new value is: " << rn3 << std::endl;
    
    std::cout << "---- Attempting to create bad fractions ----" << std::endl;
    try {
        std::cout << "Attempting to create new fraction with denominator of zero..." << std::endl;
        RationalNumber rn4(4,0);
    } catch (std::invalid_argument &ia) {
        std::cout << "EXCEPTION THROWN: " << ia.what() << std::endl;
    }
    try {
        std::cout << "Attempting to create new fraction from string with bad input..." << std::endl;
        RationalNumber rn5("23A/4");
    } catch (std::invalid_argument &ia) {
        std::cout << "EXCEPTION THROWN: " << ia.what() << std::endl;
    }
    try {
        std::cout << "Attempting to modify excisting rational number by setting denominator to zero..." << std::endl;
        RationalNumber rn6(5, 6);
        rn6.setDenominator(0);
    } catch (std::invalid_argument &ia) {
        std::cout << "EXCEPTION THROWN: " << ia.what() << std::endl;
    }
    
    
}
