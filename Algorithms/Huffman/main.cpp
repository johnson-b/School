#include <iostream>
#include <fstream>
#include "huffman.h"

int main(int argc, const char * argv[]) {
    int frequencies[huffman::MAX] = {0};
    if(argc < 2) {
        std::cout << "Invalid arguments." << std::endl;
    } else {
        std::fstream readFile;
        readFile.open(argv[1]);
        if(readFile.is_open()) {
            std::string line;
            char* ptr;
            while ( getline (readFile,line) )
            {
                ptr = &line[0u];
                while(*ptr != '\0') {
                    ++frequencies[*ptr++];
                }
            }
            readFile.close();
        }

        huffman::Node* root = huffman::Tree(frequencies);
    }

    return 0;
}