#ifndef PALINDROME_H
#define PALINDROME_H

#include <iostream>
#include "LLQueue.hpp"
#include "LLStack.hpp"

class Palindrome {
public:
    std::string input; // used to store user input
    int index; // used to keep track of index of char mismatch
    LLStack llstack;
    LLQueue llqueue;
    Palindrome(std::string&, LLStack&, LLQueue&); // constructor
    int isPalindrome(); // checks to see if user input is a palindrome
    void inStack(); // puts user string into stack
    void inQueue(); // puts user string into queue
};


#endif