#include <iostream>
#include <queue>
#include <map>
#include <iterator>
#include <algorithm>
#include "huffman.h"

int main(int argc, const char * argv[])
{
    // array used for frequency of numbers, used arbitrary
    // size of 256
    int frequencies[huffman::MAX] = {0};
    const char* ptr = argv[1];

    // move each frequency of character in phrase, into array
    while (*ptr != '\0')
        ++frequencies[*ptr++];
    
    // create huffman tree
    huffman::Node* root = huffman::Tree(frequencies);
    
    // print out string representation of tree
    huffman::TreeAsString(root);
    std::cout << std::endl;

    // map to hold characters (key) to their frequencies (value)
    std::map<char, std::vector<char>> codes;
    huffman::Codes(root, std::vector<char>(), codes);
    delete root;
    
    // print out binary representation
    ptr = argv[1];
    while (*ptr != '\0'){
        for (size_t i=0; i < codes.find(*ptr)->second.size(); i++){
            char code = codes.find(*ptr)->second[i];
            std::cout << code;
        }
        ptr++;
    }
    
    std::cout << std::endl;
    
    
    
    return 0;
}