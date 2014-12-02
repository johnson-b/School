#include <iostream>
#include "palindrome.hpp"

Palindrome::Palindrome(std::string& str, LLStack& lls, LLQueue& llq) {
    index = 0;
    input = str;
    llstack = lls;
    llqueue = llq;
    inStack();
    inQueue();
}

int Palindrome::isPalindrome() {
    char sTemp, qTemp; // temporary chars used when popping/dequeuing from stack/queue
    // check for pop/dequeu to succeed
    if(llstack.pop(sTemp) && llqueue.dequeue(qTemp)) {
        // convert characters to lowercase and then compare
        if(tolower(sTemp) == tolower(qTemp)) {
            ++index; // increase index if pop/dequeue is successful
            return isPalindrome();
        } else {
            // if chars don't match, return where the mismatch is
            return index;
        }
    } else {
        // if you reach end of string, return -1
        return -1;
    }
}

void Palindrome::inStack() {
    for (int i = 0; i < input.length(); ++i) {
        // adds only alpha chars to stack
        if (isalnum(input[i]))
            llstack.push(input[i]);
    }
}

void Palindrome::inQueue() {
    for (int i = 0; i < input.length(); ++i) {
        // adds only alpha chars to queue
        if (isalnum(input[i]))
            llqueue.enqueue(input[i]);
    }
}
