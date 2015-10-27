#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include "huffman.h"

int main(int argc, const char * argv[]) {
    int frequencies[huffman::MAX] = {0};
    std::string zeros = "00000000";
    if(argc < 2) {
        std::cout << "Invalid arguments." << std::endl;
    } else {
        std::string fileName = argv[1];
        if(fileName.find(".hzip") != std::string::npos) {
            // decode
            std::ifstream decodedFile;
            decodedFile.open(fileName.c_str(), std::ios::binary);
            struct stat fileStatus;
            stat(fileName.c_str(), &fileStatus);
            long fsize = fileStatus.st_size;
            
            char c[fsize];
            decodedFile.read(c, fsize);
            std::string s = "";
            long count = 0;
            while(count<fsize) {
                unsigned char uc =  (unsigned char) c[count];
                std::string p = ""; 
                for (int j=0; j<8 && uc>0; j++) {
                    if (uc%2==0)
                        p="0"+p;
                    else
                        p="1"+p;
                    uc=uc>>1;
                }
                p = zeros.substr(0, 8-p.size()) + p;
                s+= p;
                count++;
            }
            decodedFile.close();
        } else if(fileName.find(".txt") != std::string::npos) {
            // encode
            std::fstream readFile;
            readFile.open(fileName.c_str());
            std::string fileAsString;
            if(readFile.is_open()) {
                std::string line;
                char* ptr;
                while ( getline (readFile,line) )
                {
                    ptr = &line[0u];
                    while(*ptr != '\0') {
                        fileAsString += *ptr;
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
            
            // get name of new file and open it for write
            std::string newFileName = fileName.substr(0, fileName.find(".txt")) + ".hzip";
            std::ofstream newFile;
            newFile.open(newFileName.c_str(), std::ios::binary);
            readFile.open(fileName.c_str());
            std::string binaryString;
            if(readFile.is_open() && newFile.is_open()) {
                std::string line;
                while(getline(readFile, line)) {
                    const char * ptr = line.c_str();
                    while(*ptr != '\0') {
                        std::vector<char> code;
                        code = codes[*ptr++];
                        std::string codedStr(code.begin(), code.end());
                        binaryString+=codedStr;
                    }
                }
                
                if(binaryString.size() % 8 != 0) {
                    binaryString += zeros.substr(0, 8-binaryString.size()%8);
                }
                int binary;
                for(int i = 0; i < binaryString.size(); i+=8) {
                    binary = 1;
                    for(int j = 0; j < 8; j++) {
                        binary = binary<<1;
                        if(binaryString.at(i+j) == '1') {
                            binary += 1;
                        }
                    }
                    char c = (char)(binary & 255);
                    newFile.write(&c, 1);
                }
                readFile.close();
                newFile.close();
            }
        } else {
            std::cout << "Invalid file type." << std::endl;
        }
    }
    return 0;
}