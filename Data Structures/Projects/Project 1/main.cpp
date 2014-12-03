#include <iostream>
#include "palindrome.hpp"

int main()
{
    LLQueue llqueue;
    LLStack llstack;
    std::string input = "input";
    
    while (input.length() > 1 && input != "q")
    {
        std::cout << "Enter an alphanumeric string to check for a palindrome: " << std::endl;
        std::getline(std::cin, input);
        
        Palindrome palindrome(input, llstack, llqueue);
        std::cout << palindrome.isPalindrome() << std::endl;
    }
}

