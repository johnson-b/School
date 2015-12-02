//
//  SeamCarving.h
//  seam-carving
//
//  Created by Bryan Johnson on 11/24/15.
//  Copyright © 2015 Bryan Johnson. All rights reserved.
//

#ifndef SeamCarving_h
#define SeamCarving_h

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using pgm = std::vector<std::vector<int>>;

namespace sc {
    
    enum seamDirection {
        VERTICAL,
        HORIZONTAL
    };
    
    class SeamCarving {
    public:
        pgm image;
        pgm energy;
        pgm totalEnergy;
        int width;
        int height;
        int maxPixel;
        int vSeams;
        int hSeams;
        std::string outputFile;
        SeamCarving(std::string fileName, int vSeams, int hSeams) {
            this->vSeams = vSeams;
            this->hSeams = hSeams;
            this->readImage(fileName);
            this->outputFile = fileName.substr(0, fileName.find(".pgm")) + "_processed.pgm";
        }
        
        void readImage(std::string fileName) {
            std::fstream file;
            file.open(fileName.c_str());
            std::string line;
            // ignore first line of file
            if(file.is_open()) {
                getline(file, line);
                file >> width;
                file >> height;
                file >> maxPixel;
                
                for(int i = 0; i < height; i++) {
                    int value;
                    std::vector<int> row;
                    for(int j = 0; j < width; j++) {
                        file >> value;
                        row.push_back(value);
                    }
                    image.push_back(row);
                }
            }
        }
        
        void calculateEnergy() {
            for(size_t i = 0; i < image.size(); i++) {
                std::vector<int> eRow;
                for (size_t j = 0; j < image[i].size(); j++) {
                    int left = -1, right = -1, top = -1, bottom = -1;
                    int xE = 0, yE = 0;
                    int current = image[i][j];
                    // get left
                    if((int)j - 1 >= 0) {
                        left = image[i][j-1];
                    }
                    // get right
                    if(j + 1 < image[0].size()) {
                        right = image[i][j+1];
                    }
                    // get above
                    if((int)i - 1 >= 0) {
                        top = image[i-1][j];
                    }
                    // get below
                    if(i + 1 < image.size()) {
                        bottom = image[i + 1][j];
                    }
                    if(left != -1) {
                        if(right != -1) {
                            xE = std::abs(left - current) + std::abs(right - current);
                        } else {
                            xE = std::abs(left - current);
                        }
                    }
                    if(right != -1) {
                        if(left != -1) {
                            xE = std::abs(right - current) + std::abs(left - current);
                        } else {
                            xE = std::abs(right - current);
                        }
                    }
                    if(top != -1) {
                        if(bottom != -1) {
                            yE = std::abs(top - current) + std::abs(bottom - current);
                        } else {
                            yE = std::abs(top - current);
                        }
                    }
                    if(bottom != -1) {
                        if(top != -1) {
                            yE = std::abs(bottom - current) + std::abs(top - current);
                        } else {
                            yE = std::abs(bottom - current);
                        }
                    }
                    eRow.push_back(xE + yE);
                }
                energy.push_back(eRow);
            }
        }
        
        void calculateTotalEnergy(seamDirection d) {
            if(d == VERTICAL) {
                for(size_t i = 0; i < energy.size(); i++) {
                    std::vector<int> row;
                    for(size_t j = 0; j < energy[i].size(); j++) {
                        if(i == 0) {
                            row.push_back(energy[i][j]);
                        } else {
                            int topLeft = -1, top = -1, topRight = -1;
                            int current = energy[i][j];
                            // get top left
                            if((int)j - 1 >= 0 &&
                               (int)i - 1 >= 0) {
                                topLeft = totalEnergy[i - 1][j - 1];
                            }
                            // get top
                            if((int)i - 1 >= 0) {
                                top = totalEnergy[i-1][j];
                            }
                            // get top right
                            if(j + 1 < totalEnergy[0].size() &&
                               (int)i - 1 >= 0) {
                                topRight = totalEnergy[i - 1][j + 1];
                            }
                            int min = -1;
                            if(topLeft != -1) {
                                min = topLeft;
                            }
                            min = topLeft != -1 ? std::min(topLeft, top) : top;
                            if(topRight != -1) {
                                min = std::min(min, topRight);
                            }
                            row.push_back(min + current);
                        }
                    }
                    totalEnergy.push_back(row);
                }
            } else if(d == HORIZONTAL) {
                // ROWS ==> energy.size()
                // COLUMNS ==> energy[0].size()
                
                for(size_t i = 0; i < energy.size(); i++) {
                    std::vector<int> row;
                    row.push_back(energy[i][0]);
                    totalEnergy.push_back(row);
                }
                for(size_t j = 1; j < energy[j].size(); j++) {
                    for(size_t k = 0; k < energy.size(); k++) {
                        int leftTop = -1, left = -1, leftBottom = -1;
                        int current = energy[k][j];
                        
                        // get leftTop
                        if((int)k - 1 >= 0) {
                            leftTop = totalEnergy[k - 1][j - 1];
                        }
                        // get left
                        left = totalEnergy[k][j - 1];
                        // get leftBottom
                        if((int)k + 1 < energy.size()) {
                            leftBottom = totalEnergy[k + 1][j - 1];
                        }
                        
                        int min = -1;
                        if(leftTop != -1) {
                            min = leftTop;
                        }
                        min = leftTop != -1 ? std::min(leftTop, left) : left;
                        if(leftBottom != -1) {
                            min = std::min(min, leftBottom);
                        }
                        totalEnergy[k].push_back(min + current);
                    }
                }
            }
        }
        
        void removeVerticalSeams() {
            using iter = std::vector<int>::iterator;
            
            for(int i = 0; i < vSeams; i++) {
                this->energy.clear();
                this->totalEnergy.clear();
                this->calculateEnergy();
                this->calculateTotalEnergy(VERTICAL);
                
                std::vector<int> lastRow = totalEnergy[totalEnergy.size() - 1];
                iter start = min_element(std::begin(lastRow), std::end(lastRow));
                int col = (int)(start - lastRow.begin());
                int row = (int)totalEnergy.size() - 1;
                // starting at position totalEnergy[row][col], remove starting value
                image[row].erase(image[row].begin() + col);
                
                for(;row > 0; row--) {
                    int topLeft = -1, top = -1, topRight = -1;
                    int min = -1;
                    // get top left
                    if((int)col - 1 >= 0 &&
                       (int)row - 1 >= 0) {
                        topLeft = totalEnergy[row - 1][col - 1];
                    }
                    // get top
                    if((int)row - 1 >= 0) {
                        top = totalEnergy[row-1][col];
                    }
                    // get top right
                    if(col + 1 < (int)totalEnergy[0].size() &&
                       (int)row - 1 >= 0) {
                        topRight = totalEnergy[row - 1][col + 1];
                    }
                    
                    if(topLeft != -1) {
                        min = topLeft;
                    }
                    min = min != -1 ? std::min(topLeft, top) : top;
                    if(topRight != -1) {
                        min = std::min(min, topRight);
                    }
                    
                    int temp = col;
                    if(min == topLeft) {
                        col = col - 1;
                    }
                    if(min == topRight &&
                       temp == col) {
                        col = col + 1;
                    }
                    
                    image[row - 1].erase(image[row - 1].begin() + col);
                }
            }
        }
        
        void removeHorizontalSeams() {
            using iter = std::vector<int>::iterator;
            
            for(int i = 0; i < hSeams; i++) {
                this->energy.clear();
                this->totalEnergy.clear();
                this->calculateEnergy();
                this->calculateTotalEnergy(HORIZONTAL);
                
                // TODO: CHANGE THIS SHIT
                std::vector<int> firstColumn;// = totalEnergy[totalEnergy.size() - 1];
//                iter start = min_element(std::begin(lastRow), std::end(lastRow));
//                int col = (int)(start - lastRow.begin());
//                int row = (int)totalEnergy.size() - 1;
//                // starting at position totalEnergy[row][col], remove starting value
//                image[row].erase(image[row].begin() + col);
//                
//                for(;row > 0; row--) {
//                    int topLeft = -1, top = -1, topRight = -1;
//                    int min = -1;
//                    // get top left
//                    if((int)col - 1 >= 0 &&
//                       (int)row - 1 >= 0) {
//                        topLeft = totalEnergy[row - 1][col - 1];
//                    }
//                    // get top
//                    if((int)row - 1 >= 0) {
//                        top = totalEnergy[row-1][col];
//                    }
//                    // get top right
//                    if(col + 1 < (int)totalEnergy[0].size() &&
//                       (int)row - 1 >= 0) {
//                        topRight = totalEnergy[row - 1][col + 1];
//                    }
//                    
//                    if(topLeft != -1) {
//                        min = topLeft;
//                    }
//                    min = min != -1 ? std::min(topLeft, top) : top;
//                    if(topRight != -1) {
//                        min = std::min(min, topRight);
//                    }
//                    
//                    int temp = col;
//                    if(min == topLeft) {
//                        col = col - 1;
//                    }
//                    if(min == topRight &&
//                       temp == col) {
//                        col = col + 1;
//                    }
//                    
//                    image[row - 1].erase(image[row - 1].begin() + col);
//                }
            }
        }
        
        void processImage() {
//            this->removeVerticalSeams();
            this->removeHorizontalSeams();
            std::ofstream pFile;
            pFile.open(this->outputFile);
            if(pFile.is_open()) {
                pFile << "P2\n";
                pFile << image[0].size();
                pFile << " ";
                pFile << image.size();
                pFile << "\n";
                pFile << "255\n";
                for(size_t i = 0; i < image.size(); i++) {
                    for (size_t j = 0; j < image[i].size(); j++) {
                        pFile << image[i][j];
                        pFile << " ";
                    }
                    pFile << "\n";
                }
            }
            pFile.close();
        }
        
        void printImage() {
            for(size_t i = 0; i < image.size(); i++) {
                for (size_t j = 0; j < image[i].size(); j++) {
                    std::cout << image[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
        
        void printEnergy() {
            for(size_t i = 0; i < energy.size(); i++) {
                for (size_t j = 0; j < energy[i].size(); j++) {
                    std::cout << energy[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
        
        void printTotalEnergy() {
            for(size_t i = 0; i < totalEnergy.size(); i++) {
                for (size_t j = 0; j < totalEnergy[i].size(); j++) {
                    std::cout << totalEnergy[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
    };
}

#endif /* SeamCarving_h */