#include <iostream>
#include <fstream>
#include <string>
#include "huffman.h"

int main(int argc, const char * argv[]) {
    int frequencies[huffman::MAX] = {0};
    if(argc < 2) {
        std::cout << "Invalid arguments." << std::endl;
    } else {
        std::string fileName = argv[1];
        if(fileName.find(".hzip") != std::string::npos) {
            // decode
            std::cout << "Decode file!" << std::endl;
        } else if(fileName.find(".txt") != std::string::npos) {
            // encode
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
            std::map<char, std::vector<char> > codes;
            huffman::Compress(root, std::vector<char>(), codes);

            huffman::PrintFrequencyTable(root, codes);
            huffman::TreeAsStringPost(root);
            std::cout << std::endl;

            // get name of new file
            std::string newFile = fileName.substr(0, fileName.find(".txt")) + ".hzip";
            std::cout << "Output File Name: " << newFile << std::endl;




        } else {
            std::cout << "Invalid file type." << std::endl;    
        }
    }
    return 0;
}

// int main(int argc, const char * argv[])
// {
//     // Build frequency table
//     int frequencies[huffman::MAX] = {0};
//     const char* ptr = argv[1];
//     while (*ptr != '\0')
//         ++frequencies[*ptr++];

//     huffman::Node* root = huffman::Tree(frequencies);

//     huffman::TreeAsString(root);
//     std::cout << std::endl;

//     std::map<char, std::vector<char>> codes;
//     huffman::Codes(root, std::vector<char>(), codes);
//     delete root;

//     ptr = argv[1];
//     while (*ptr != '\0'){
//         for (size_t i=0; i < codes.find(*ptr)->second.size(); i++){
//             char code = codes.find(*ptr)->second[i];
//             std::cout << code;
//         }
//         ptr++;
//     }

//     std::cout << std::endl;



//     return 0;
// }